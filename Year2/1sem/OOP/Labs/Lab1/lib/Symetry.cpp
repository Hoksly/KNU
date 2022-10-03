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

Line Symetry::symetry(Line base_line, Line line_to_sym)
{
    // symetry of line_to_sym by base_line

    if (base_line.is_paralel(line_to_sym))
    {
        Point A(0, line_to_sym.b()); // just a point on a line
        Point B(-line_to_sym.b() / line_to_sym.k(), 0);

        Point A_sym = symetry(A, base_line);
        Point B_sym = symetry(B, base_line);

        return Line(A_sym, B_sym);
    }

    Point interception_point = base_line.intercept(line_to_sym)[0]; // it will be exactly one point
    Point random_point = line_to_sym.random_point();

    while (interception_point == random_point)
        random_point = line_to_sym.random_point();

    Point symetrical_random_point = symetry(random_point, base_line);

    return Line(interception_point, symetrical_random_point);
}

Circle Symetry::symetry(Circle C, Line l)
{
    Point new_O = symetry(C.O(), l);

    return Circle(new_O, C.r());
}

Point Symetry::symetry(Circle C, Point A)
{
}