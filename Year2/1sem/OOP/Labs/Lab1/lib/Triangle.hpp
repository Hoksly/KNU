#include "Figure.hpp"
#include "Point.hpp"

#ifndef _TRIANGLE_HPP
#define _TRIANGLE_HPP
class Triangle : Figure
{
private:
    Point _A, _B, _C;

public:
    Triangle(Point A, Point B, Point C) : _A(A), _B(B), _C(C) {}
    Point A() { return _A; }
    Point B() { return _B; }
    Point C() { return _C; }
};

#endif