#include "Line.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"
#include "Vector.hpp"

#ifndef _SYMETRY_HPP
#define _SYMETRY_HPP
class Symetry
{
public:
    static Line symetry(Line, Line);
    static Point symetry(Point, Line);
    static Triangle symetry(Triangle, Line);
    static Point symetry(Point, Circle);
    static Circle symetry(Circle, Line);
};

#endif
