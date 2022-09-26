#include "Line.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"

class Symetry
{
public:
    static Line symetry(Line, Line);
    static Point symetry(Point, Line);
    static Triangle symetry(Triangle, Line);
    static Circle symetry(Circle, Line);
};