#ifndef _CANVAS_H
#define _CANVAS_H

#include "shape.h"
#include <vector>
#include <istream>
#include <ostream>
#include <gtkmm.h>

class Canvas : public Gtk::DrawingArea {
  public:
    Canvas(Gtk::Window& window);

    // Constants for drawing mode
    static const int PEN_MODE_SEGMENT = 1;
    static const int PEN_MODE_CONTIGUOUS = 2;
    static const int PEN_MODE_FREEHAND = 3;
    void set_pen_mode(int mode);

    // Specify pen color for subsequent lines
    void set_pen_color(Gdk::RGBA new_color);
    Gdk::RGBA get_pen_color();

    // Specify pen width for subsequent lines
    void set_pen_width(double new_width);
    double get_pen_width();

    // Specify pen dash for subsequent lines
    void set_pen_dash(int dash);
    int get_pen_dash();

    // Add shapes and points
    void add_shape(Graph_lib::Shape& shape);
    void add_point(Graph_lib::Point& point); // To last added shape

    // Manage file I/O
    std::string get_filename();
    void set_filename(std::string filename);
    void save(std::ostream& ost);
    bool saved(); // True if all data has been saved
    void new_drawing();
    void load(std::istream& ist);

    // Undo most recent shape
    void undo();

    // Response to an attempt to close the main window
    bool on_my_delete_event(GdkEventAny* event);
    bool drawing_is_unsaved();  // Dialog re saving data
  protected:
    // Respond to gtkmm events
    bool on_button_press_event(GdkEventButton * event) override;
    bool on_motion_notify_event(GdkEventMotion * event) override;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  private:
    // All of the shapes on the canvas
    std::vector<Graph_lib::Shape*> shapes;
    void new_line(int _x1, int _y1, int _x2, int _y2);

    // Current filename and main window 
    std::string _filename;
    Gtk::Window& win;

    // Data for managing the actual drawing process
    bool dirty;              // True if any changes since last save
    int x1, y1;              // Coordinates of most recent click
    int pen_mode;            // What shape is being drawn - see constants above
    int previous_pen_mode;   // What shape was being drawn LAST click, to detect changes
    int click_in_progress;   // distinguish 1st click from subsequent while drawing
    int points_added;        // Number of points added per shape
    Gdk::RGBA _color;        // The current drawing color and opacity
    double _width;           // The current line width
    int _dash;               // The current dash pattern (index into dashes)
};

#endif
