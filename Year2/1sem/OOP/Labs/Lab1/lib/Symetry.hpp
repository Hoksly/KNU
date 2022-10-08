#include "Line.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"
#include "Vector.hpp"
#include "boost/variant.hpp"
#ifndef _SYMETRY_HPP
#define _SYMETRY_HPP

typedef boost::variant<Line, Circle> inversion_res;

class Symetry
{
private:
    static Point __midpoint(Point A, Point B);

public:
    static Line symetry(Line, Line);
    static Point symetry(Point, Line);
    static Triangle symetry(Triangle, Line);
    static Circle symetry(Circle, Line);

    static Point inversion(Point, Circle);
    static inversion_res inversion(Line, Circle);
    static Triangle inversion(Triangle, Circle);
    static inversion_res inversion(Circle, Circle);
};

#endif
