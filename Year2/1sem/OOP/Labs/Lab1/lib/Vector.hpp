#include <string>
#include <cmath>
#include <iostream>
#include "Point.hpp"

using std::operator+;
using std::operator-;
using std::operator==;

class Vector
{
    double _x, _y;

public:
    // Constructors
    Vector(double x, double y) : _x(x), _y(y) {}
    Vector(std::pair<double, double> p) : _x(p.first), _y(p.second) {}
    Vector(Point a, Point b);

    // Getters
    inline double x() { return _x; }
    inline double y() { return _y; }

    // Other Methods
    void scale_to(double target_len);

    Vector operator+(Vector);
    Vector operator-(Vector);
    Vector operator==(Vector);
    inline operator std::pair<double, double>() const { return std::make_pair(_x, _y); }

    std::string str();
    std::pair<double, double> pair();
    void print();
};