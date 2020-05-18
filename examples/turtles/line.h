#ifndef _LINE_H
#define _LINE_H

class Line {    // Define a line from (x1, y1) to (x2, y2)
     double _x1, _y1, _x2, _y2;
   public:
     Line(double p_x1, double p_y1,double p_x2, double p_y2);
     double x1();
     double y1();
     double x2();
     double y2();
};
#endif
