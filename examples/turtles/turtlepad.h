#ifndef _TURTLEPAD_H
#define _TURTLEPAD_H

#include "line.h"
#include <vector>
#include <gtkmm.h>

class Turtlepad : public Gtk::DrawingArea {
  public:
    Turtlepad();
    void penUp();
    void penDown();
    void turn(double degrees);
    void forward(double distance);
  protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  private:
    std::vector<Line> lines; // Where the turtle dragged its tail
    const double d2r;        // Degrees to radians
    double x, y, angle;      // Current turtle position
    bool pen_is_down;        // True if the turtle is dragging its tail
};
#endif
