#include "Point.hpp"
#include <cmath>
#include <random>

#ifndef _CIRCLE_HPP
#define _CIRCLE_HPP
class Circle
{
    Point _O;
    double _r;

public:
    Circle(Point O, double r) : _O(O), _r(r){};
    Circle() = default;

    inline double r() { return _r; }
    inline Point O() { return _O; }
    inline bool passes_trough(Point A) { return fabs(_O.distance_to(A) - _r) < 1.e-5; }

    inline std::string str() { return "(x-" + std::to_string(_O.x()) + ")^2 + (y-" + std::to_string(_O.y()) + ")^2 = " + std::to_string(_r) + "^2"; }

    Point random_point();
};

#endif
