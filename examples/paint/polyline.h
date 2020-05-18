#ifndef _POLYLINE_H
#define _POLYLINE_H
#include "shape.h"

namespace Graph_lib { 
class Polyline : public Shape {
   public:
     Polyline(Gdk::RGBA color = Gdk::RGBA("blue"), double width = 3.0, int dash = 0);
     Polyline(std::istream& ist);
     virtual Polyline* clone() override; // Creates object copy on heap
};
}
#endif
