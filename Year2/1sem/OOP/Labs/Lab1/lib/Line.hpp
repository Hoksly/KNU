
#include "Point.hpp"
#include <string>
#include <vector>
#include <random>
#include <stdlib.h>
#include <cmath>

#include "Vector.hpp"
#include "Figure.hpp"

#ifndef _LINE_HPP
#define _LINE_HPP
class Line
{
    // y = kx + b
    double _k;
    double _b;
    double _angle;

public:
    Line(Point A, Point B);
    Line(Point A, Vector v);

    inline double k() { return _k; }
    inline double b() { return _b; }
    inline double angle() { return _angle; }

    std::string str();
    std::pair<double, double> pair();

    std::vector<Point> intercept(Line);
    bool passes_through(Point);
    bool is_paralel(Line);

    Vector normal_vecor();

    Point random_point(); // returns a random point on a line
};

#endif
