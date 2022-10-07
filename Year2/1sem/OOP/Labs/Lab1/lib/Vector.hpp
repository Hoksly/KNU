#include <string>
#include <cmath>
#include <iostream>
#include "Point.hpp"

using std::operator+;
using std::operator-;
using std::operator==;

#ifndef _VECTOR_HPP
#define _VECTOR_HPP
class Vector : Figure
{
    double _x, _y;

public:
    // Constructors
    Vector(double x, double y) : _x(x), _y(y) {}
    Vector(std::pair<double, double> p) : _x(p.first), _y(p.second) {}
    Vector(Point a, Point b);

    // Getters
    inline double x() const { return _x; }
    inline double y() const { return _y; }

    // Other Methods
    void scale_to(double target_len);
    void rotate_right(double angle_rad);
    void rotate_90();

    Vector operator+(Vector);
    Vector operator-(Vector);
    bool operator==(const Vector &A) const;
    inline operator std::pair<double, double>() const { return std::make_pair(_x, _y); }

    std::string str() const override;
    std::pair<double, double> pair() const;
    void print();
};

#endif