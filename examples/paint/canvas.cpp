#include "canvas.h"
#include "line.h"
#include "polyline.h"
#include <vector>
#include <stdlib.h>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <istream>
#include <ostream>
#include <fstream>
#include <gtkmm.h>
#include <cairomm/context.h>

// Get reference to current window to avoid discouraging warnings
Canvas::Canvas(Gtk::Window& window) : win{window}, 
    pen_mode{PEN_MODE_SEGMENT}, previous_pen_mode{PEN_MODE_SEGMENT}, 
    dirty{false}, x1{0}, y1{0}, click_in_progress{0}, points_added{0}, 
    _width{3}, _dash{0}, _color{Gdk::RGBA("blue")},
    _filename{"untitled.ctp"} {
    add_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::POINTER_MOTION_MASK);
}

std::string Canvas::get_filename() {return _filename;}
void Canvas::set_filename(std::string filename) {_filename = filename;}
void Canvas::save(std::ostream& ost) {
  for (Graph_lib::Shape* s : shapes) {
      ost << typeid(*s).name() << ' '; // Write the name of the actual type
      s->save(ost);
      ost << std::endl;  // one line per shape (this is ignored when loading)
  }
  dirty = false;
}
// True if all data has been written to disk
bool Canvas::saved() {
    return !dirty;
}

// Set the shape that we're drawing
void Canvas::set_pen_mode(int mode) {pen_mode = mode;}

void Canvas::new_drawing() {
    if (drawing_is_unsaved()) return;
    shapes.clear(); // Delete all drawing information
    dirty = false;
}
void Canvas::load(std::istream& ist) {
    dirty = (shapes.size() > 0);
    while(ist) {
        std::string typetag;
        ist >> typetag;
        if (typetag == "N9Graph_lib4LineE") {
            Graph_lib::Line l{ist}; 
            shapes.push_back(l.clone());
        } else if (typetag == "N9Graph_lib8PolylineE") {
            Graph_lib::Polyline l{ist};
            shapes.push_back(l.clone());
        }
    }
}

// Specify pen color for subsequent lines
Gdk::RGBA Canvas::get_pen_color() {return _color;}
void Canvas::set_pen_color(Gdk::RGBA new_color) {
    _color = new_color;
}

// Set and get the pen width
double Canvas::get_pen_width() {return _width;}
void Canvas::set_pen_width(double new_width) {
    _width = new_width;
}

// Set and get the pen dash
int Canvas::get_pen_dash() {return _dash;}
void Canvas::set_pen_dash(int new_dash) {
    _dash = new_dash;
}

// Add a shape to the vector
void Canvas::new_line(int _x1, int _y1, int _x2, int _y2) {
    if (pen_mode == PEN_MODE_SEGMENT) {
        Graph_lib::Line line{Graph_lib::Point{_x1, _y1}, Graph_lib::Point{_x2, _y2}, _color, _width, _dash};
        add_shape(line);
    } else if ((pen_mode == PEN_MODE_CONTIGUOUS) || (pen_mode == PEN_MODE_FREEHAND)) {
        if ((click_in_progress == 1) || (points_added == 0)) {
            Graph_lib::Polyline polyline{_color, _width, _dash};
            Graph_lib::Point p{_x1, y1};
            polyline.add_point(p);
            add_shape(polyline);
        }
        Graph_lib::Point p{_x2, _y2};
        add_point(p);
    } else {
        throw std::runtime_error{"Invalid pen_mode"};
    }
    dirty = true;
}

void Canvas::add_shape(Graph_lib::Shape& shape) {
    shapes.push_back(shape.clone());
}
void Canvas::add_point(Graph_lib::Point& point) {
    if (shapes.empty()) throw std::runtime_error{"Attempted to add point to empty shapes vector"};
    shapes.back()->add_point(point);
}

// Undo (remove last shape)
void Canvas::undo() {
    if (shapes.empty()) return;
    delete shapes.back();
    shapes.pop_back();
    queue_draw();
}

// Mouse click event handler (for discrete clicks)
bool Canvas::on_button_press_event(GdkEventButton * event) {
    // If this is a left-mouse button press, we're interested!
    if( (event->type == GDK_BUTTON_PRESS) && (event->button == 1)) {

        // This event not for freehand mode
        if (pen_mode == PEN_MODE_FREEHAND) return false;

        // If the pen mode changed, clear click and point counters
        if (pen_mode != previous_pen_mode) {
            click_in_progress = 0;
            points_added = 0; 
        }

        // Just remember the coordinates on the first click, but add a new line 
        // on the second click (and subsequent clicks in contiguous mode)

        if (click_in_progress == 0) {
            x1 = event->x;
            y1 = event->y;
            ++click_in_progress;
        } else {
            int x2 = event->x;
            int y2 = event->y;
            new_line(x1, y1, x2, y2);
            queue_draw();  // initiate screen refresh
            x1 = x2;       // to support contiguous mode
            y1 = y2;
            if (pen_mode == PEN_MODE_SEGMENT) click_in_progress = 0;
            else ++click_in_progress;
        }
        previous_pen_mode = pen_mode;

        return true; // We handled this event
    }
    return false;  // We did NOT handle this event
}

// Drag mouse event handler (for scribbling)
bool Canvas::on_motion_notify_event(GdkEventMotion * event) {

    // Only allow freehand drawing if the mode is selected
    if (pen_mode != PEN_MODE_FREEHAND) return false;

    // If the pen mode changed, clear the point counter
    if (pen_mode != previous_pen_mode) points_added = 0;

    int x2 = (int)event->x;
    int y2 = (int)event->y;
    guint state = event->state;

    // If the button is down, add points to the Polyline
    if (state & Gdk::BUTTON1_MASK) {
        new_line(x1, y1, x2, y2);
        queue_draw();  // initiate screen refresh
        ++points_added;
    // If not, signal a new Polyline is pending the next button press
    } else {
        points_added = 0;
    }
    // Always track the cursor in freehand mode
    x1 = x2;
    y1 = y2;

    previous_pen_mode = pen_mode;
    click_in_progress = 0; 
    return true;
}

// Draw the lines any time gtkmm needs to refresh the widget
bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // If nothing to draw, we're done
    if (shapes.size() == 0) return true;

    // Create a Cairomm context to manage our drawing
    Gtk::Allocation allocation = get_allocation();

    // Draw the lines
    for(Graph_lib::Shape* s : shapes) {
        s->draw(cr);
    }

    // Drawing was successful
    return true;
}

bool Canvas::on_my_delete_event(GdkEventAny* event) {
    return drawing_is_unsaved();
}

bool Canvas::drawing_is_unsaved() {
  if (saved()) return false;
  Gtk::MessageDialog d{win, "Unsaved data will be lost", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE};
  d.add_button("Save", 1);
  d.add_button("Discard", 2);
  d.add_button("Cancel", 3);
  int response = d.run();
  if (response == 1) {
    // Save data and exit
    std::ofstream ofs{get_filename()};
    save(ofs);
    return false;
  } else if (response == 2) {
    // Discard data and exit
    return false;
  } else {
    return true;
  }
}

