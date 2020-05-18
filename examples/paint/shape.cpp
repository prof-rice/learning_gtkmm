#include "shape.h"
#include <gtkmm.h>
#include <cairomm/context.h>
#include <typeinfo>

namespace Graph_lib {   // our graphics interface
Shape::Shape(Gdk::RGBA color, double width, int dash) : _color{color}, _width{width}, _dash{dash} { }
Shape::Shape(std::istream& ist) {
  int size;
  std::string rgba_color;

  ist >> size;
  for (int i=0; i<size; ++i) points.push_back(Point{ist});
  ist >> rgba_color >> _width >> _dash;
  _color = Gdk::RGBA{rgba_color};
}

void Shape::save(std::ostream& ost) {
  ost << points.size() << ' ';
  for (Point p : points) p.save(ost);
  ost << _color.to_string() << ' ' << _width << ' ' << _dash << ' ';
}

void Shape::add_point(Point p) {
    points.push_back(p);
}

void Shape::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gdk::Cairo::set_source_rgba(cr, _color);
    cr->set_line_width(_width);
    cr->set_dash(dashes[_dash], 0.0);
    int i = 0;
    for (const Point& p : points)
        if (!i++) cr->move_to(p.x(), p.y());
        else cr->line_to(p.x(), p.y());
    cr->stroke();
}

std::ostream& operator<<(std::ostream& ost, Shape& s) {
    int i = 0;
    for (const Point& p : s.points) {
        if (i++) ost << "->";
        ost << p;
    }
    return ost;
}
}

