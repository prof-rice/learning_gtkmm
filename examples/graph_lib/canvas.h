#ifndef _CANVAS_H
#define _CANVAS_H

#include "shape.h"
#include <vector>
#include <gtkmm/drawingarea.h>

namespace Graph_lib {
class Canvas : public Gtk::DrawingArea {
  public:
    void add_shape(Shape& shape);
  protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  private:
    std::vector<Shape*> shapes;
    int updates = 0;
};
}
#endif
