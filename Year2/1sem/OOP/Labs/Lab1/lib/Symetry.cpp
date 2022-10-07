#include "Symetry.hpp"

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
    Point new_B = symetry(T.B(), l);
    Point new_C = symetry(T.C(), l);

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

Point Symetry::inversion(Point A, Circle C)
{
    Vector OA(C.O(), A);

    double OA_len = A.distance_to(C.O());
    double OB_len = pow(C.r(), 2) / OA_len;

    OA.scale_to(OB_len);
    Point B = C.O();

    B.move(OA.x(), OA.y());
    return B;
}

Triangle Symetry::inversion(Triangle T, Circle C)
{
    return Triangle(inversion(T.A(), C), inversion(T.B(), C), inversion(T.C(), C));
}

inversion_res Symetry::inversion(Circle C1, Circle C)
{
    // passes through inversion center
    if (C1.passes_trough(C.O()))
    {
        Vector normal_vector(C.O(), C1.O());
        Point point_on_a_line = inversion(C1.O(), C);
        return Line(point_on_a_line, normal_vector);
    }

    // in this case it will inverse into a circle

    Line center_line(C.O(), C1.O());

    std::vector<Point> interceptions = center_line.intercept(C1);
    std::cout << "Point1: " << interceptions[0].str() << std::endl;
    std::cout << "Point2: " << interceptions[1].str() << std::endl;

    // points must be diametrically oposed
    assert(fabs(interceptions[0].distance_to(interceptions[1]) - C.r() * 2) < 1.e-5);

    Point A1 = inversion(interceptions[0], C);
    Point B1 = inversion(interceptions[0], C);

    Point new_O((A1.x() + B1.x()) / 2, (A1.y() + B1.y()) / 2);
    double new_R = new_O.distance_to(A1);

    return Circle(new_O, new_R);
}

inversion_res Symetry::inversion(Line l1, Circle C)
{
    if (l1.passes_through(C.O()))
        return l1;

    Vector normal = l1.normal_vecor();

    Line interception_line = Line(C.O(), normal);
    std::cout << "Line:  " << interception_line.str() << std::endl;

    Point interception_of_target_line = interception_line.intercept(l1)[0];
    std::cout << "Point1: " << interception_of_target_line.str() << std::endl;

    Point new_circle_center = inversion(interception_of_target_line, C);
    std::cout << "Center: " << new_circle_center.str() << std::endl;

    // using that inversed circle will always pass through inversion center

    double new_r = new_circle_center.distance_to(C.O());

    return Circle(new_circle_center, new_r);
}