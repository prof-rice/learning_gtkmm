#ifndef __SHAPE_H
#define __SHAPE_H

#include "point.h"
#include <vector>
#include <string>
#include <istream>
#include <ostream>
#include <gdkmm/rgba.h>
#include <cairomm/context.h>
namespace Graph_lib {   // our graphics interface
typedef std::vector<double> dash_pattern;  // A dash pattern is a vector of doubles
const std::vector<dash_pattern> dashes = { // The available dash pattern
         {8.0, 0.0},
         {8.0, 8.0},
         {8.0, 4.0},
         {8.0, 4.0, 2.0, 4.0},
};

// A shape holds points connected by lines
class Shape {
  public:
    Shape(Gdk::RGBA color = Gdk::RGBA("blue"), double width = 3.0, int dash = 0);
    Shape(std::istream& ist);  // Recreate the Shape from a stream

    // Writes the Shape data to a stream
    virtual void save(std::ostream& ost);
    //virtual std::string typetag() = 0; // Tag to identify which class this is

    // Appends a new point to the shape
    virtual void add_point(Point p);

    // Draws the shape (called from gtkmm's on_draw method)  
    virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr);

    // This method copies the current object onto the heap and 
    // returns a pointer to it. This builds our vector of pointers 
    // to objects derived from Shape, to polymorphically call draw().
    virtual Shape* clone() = 0;

    // Output stream shows the points that comprise the shape
    friend std::ostream& operator<<(std::ostream& ost, Shape& s);
  protected:
    std::vector<Point> points;
    Gdk::RGBA _color;
    double _width;
    int _dash;
};
}
#endif
