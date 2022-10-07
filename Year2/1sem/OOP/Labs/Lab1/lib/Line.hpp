
#include "Point.hpp"
#include <string>
#include <vector>
#include <random>
#include <stdlib.h>
#include <cmath>

#include "Vector.hpp"
#include "Figure.hpp"
#include "Circle.hpp"

#ifndef _LINE_HPP
#define _LINE_HPP
class Line : Figure
{
    // y = kx + b
    double _k;
    double _b;
    double _angle;

    std::vector<double> __solve_quadratic_eqasion(double a, double b, double c);

public:
    Line(Point A, Point B);
    Line(Point A, Vector v);
    Line(double k, double b) : _k(k), _b(b) {}
    Line() = default;

    inline double k() { return _k; }
    inline double b() { return _b; }
    inline double angle() { return _angle; }

    std::string str() const override;
    std::pair<double, double> pair();

    std::vector<Point> intercept(Line);
    std::vector<Point> intercept(Circle);

    bool passes_through(Point);

    bool is_paralel(Line);

    Vector normal_vecor();

    Point random_point(); // returns a random point on a line
};

#endif
