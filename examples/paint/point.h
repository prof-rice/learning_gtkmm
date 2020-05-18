#ifndef __POINT_H
#define __POINT_H
#include <iostream>

namespace Graph_lib {   // our graphics interface
class Point {      // a Point is a pair of ints
    public:
      Point(int x, int y);
      Point(std::istream& ist);  // Recreate point from a stream
      void save(std::ostream& ost);   // Write constructor-compatible data to stream
      int x() const;
      int y() const;
      bool operator==(Point rhs);
      bool operator!=(Point rhs);
      friend std::ostream& operator<<(std::ostream& ost, const Point& p);
    private:
      int _x;
      int _y;		
};
}
#endif

