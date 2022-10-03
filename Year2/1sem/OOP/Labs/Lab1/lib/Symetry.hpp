#include "Line.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"

#ifndef _SYMETRY_HPP
#define _SYMETRY_HPP
class Symetry
{
public:
    static Line symetry(Line, Line);
    static Point symetry(Point, Line);
    static Triangle symetry(Triangle, Line);
    static Circle symetry(Circle, Point);
    static Circle symetry(Circle, Line);
};

#endif
