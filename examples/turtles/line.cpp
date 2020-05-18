#include "line.h"

Line::Line(double p_x1, double p_y1,double p_x2, double p_y2) 
        : _x1{p_x1}, _y1{p_y1}, _x2{p_x2}, _y2{p_y2} { }

double Line::x1() {return _x1;}
double Line::y1() {return _y1;}
double Line::x2() {return _x2;}
double Line::y2() {return _y2;}
