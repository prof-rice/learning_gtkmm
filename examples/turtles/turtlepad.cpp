#include "turtlepad.h"
#include "line.h"
#include <cmath>

Turtlepad::Turtlepad() : d2r{M_PI/180.0}, x{0}, y{0}, angle{0}, pen_is_down{true} { }
void Turtlepad::penUp() {pen_is_down = false;}
void Turtlepad::penDown() {pen_is_down = true;}
void Turtlepad::turn(double degrees) {angle += degrees * d2r;}
void Turtlepad::forward(double distance) {
  double x2 = x + distance*cos(angle);
  double y2 = y + distance*sin(angle);
  if (pen_is_down) lines.push_back(Line(x, y, x2, y2));
  x = x2;
  y = y2;
}

// Draw the lines any time gtkmm needs to refresh the widget
bool Turtlepad::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // If nothing to draw, we're done
    if (lines.size() == 0) return true;

    // Create a Cairomm context to manage our drawing
    Gtk::Allocation allocation = get_allocation();

    // Center the drawing in the window
    const double width = allocation.get_width();
    const double height = allocation.get_height();
    cr->translate(width / 2, height / 2);

    // Use a 3 pixel wide red line
    cr->set_line_width(3.0);
    cr->set_source_rgb(0.8, 0.0, 0.0); // Set lines to red

    // Draw the lines
    for(Line l : lines) {
        cr->move_to(l.x1(), l.y1());
        cr->line_to(l.x2(), l.y2());
    }

    // Apply the colors to the window
    cr->stroke();

    // Drawing was successful
    return true;
}

