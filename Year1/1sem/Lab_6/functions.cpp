#include "classes.h"

typedef long double coordinate;

coordinate Det2x2(coordinate a11, coordinate a12, coordinate a21, coordinate a22)
{
    return a11 * a22 - a12 * a21;
}


Point VectorProduct(const Point& A, const Point& B, const Point& C)
{
    Point a = B - A;
    Point b = C - A;
    return Point (Det2x2(a.y, a.z, b.y, b.z),
                  Det2x2(a.x, a.z, b.x, b.z),
                  Det2x2(a.x, a.y, b.x, b.y));
}


int main()
{
    Point a(1, 0, 0);
}