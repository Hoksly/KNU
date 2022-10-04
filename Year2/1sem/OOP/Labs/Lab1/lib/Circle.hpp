#include "Point.hpp"

#ifndef _CIRCLE_HPP
#define _CIRCLE_HPP
class Circle
{
    Point _O;
    double _r;

public:
    Circle(Point O, double r) : _O(O), _r(r){};

    inline double r() { return _r; }
    inline Point O() { return _O; }
};

#endif
