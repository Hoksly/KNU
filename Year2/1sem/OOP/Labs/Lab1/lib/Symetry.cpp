#include "Symetry.hpp"
#include <vector>
Point Symetry::symetry(Point A, Line l)
{
    if (l.passes_through(A))
        return A;

    Vector normal = l.normal_vecor();

    Line interception_line = Line(A, normal);

    Point interception = l.intercept(interception_line)[0];

    Vector distance(A, interception);

    interception.move((std::pair<double, double>)distance);

    return interception;
}

Triangle Symetry::symetry(Triangle T, Line l)
{
    Point new_A = symetry(T.A(), l);
    Point new_B = symetry(T.A(), l);
    Point new_C = symetry(T.A(), l);

    return Triangle(new_A, new_B, new_C);
}

Circle Symetry::symetry(Circle C, Line l)
{
    Point new_O = symetry(C.O(), l);

    return Circle(new_O, C.r());
}