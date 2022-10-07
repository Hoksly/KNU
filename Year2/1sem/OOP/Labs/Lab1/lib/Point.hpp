#include <string>
#include <cmath>
#include "Figure.hpp"

#ifndef _POINT_HPP
#define _POINT_HPP
class Point : Figure
{

    double _x, _y;

public:
    Point(double x, double y) : _x(x), _y(y) {}
    Point(std::pair<double, double> p) : _x(p.first), _y(p.second) {}
    Point() = default;

    inline double x() const { return _x; }
    inline double y() const { return _y; }

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

    bool operator==(const Point &B) const { return fabs(_x - B._x) < 1.e-5 && fabs(_y - B._y) < 1.e-5; }

    double distance_to(Point B) { return sqrt(pow(_x - B._x, 2) + pow(_y - B._y, 2)); }

    std::string str() const override { return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ")"; }
};

#endif
