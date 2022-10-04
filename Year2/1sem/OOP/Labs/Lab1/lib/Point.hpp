#include <string>
#include <cmath>
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

    void move(double x, double y)
    {
        _x += x;
        _y += y;
    }
    void move(std::pair<double, double> v)
    {
        _x += v.first;
        _y += v.second;
    };

    bool operator==(const Point &B) { return _x == B._x && _y == B._y; }

    double distance_to(Point B) { return pow(_x - B._x, 2) + pow(_y - B._y, 2); }
};

#endif
