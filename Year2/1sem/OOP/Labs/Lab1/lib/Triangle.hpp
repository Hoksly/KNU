#include "Point.hpp"

class Triangle
{
private:
    Point _A, _B, _C;

public:
    Triangle(Point A, Point B, Point C);
    Point A() { return _A; }
    Point B() { return _B; }
    Point C() { return _C; }
};

Triangle::Triangle(Point A, Point B, Point C)
{
}

Triangle::~Triangle()
{
}
