#include <string>

#include "Figure.hpp"

#ifndef _POINT_HPP
#define _POINT_HPP
class Point
{

    double _x, _y;

public:
    Point(double x, double y) : _x(x), _y(y) {}
    Point(std::pair<double, double> p) : _x(p.first), _y(p.second) {}

    inline double x() { return _x; }
    inline double y() { return _y; }

    inline std::pair<double, double> get() { return std::make_pair(_x, _y); }

    void move(double x, double y);
    void move(std::pair<double, double> v);

    bool operator==(const Point &B) { return _x == B._x && _y == B._y; }
};

#endif
