#include "/home/hoksly/Github/KNU/Year2/1sem/OOP/Labs/Lab1/doctest/doctest/doctest.h"
#include "Symetry.hpp"

TEST_CASE("Point-Line symetry")
{
    Symetry s;

    Point A(0, 0);
    Point B(0, 5);

    Line l(Point(1, 1), Point(5, 5));
    CHECK(l.b() == 0);
    CHECK(l.k() == 1);

    Point A_sym = s.symetry(A, l);
    Point B_sym = s.symetry(B, l);

    CHECK_EQ(A.x(), A_sym.x()); // A lies on a line l;
    CHECK_EQ(A.y(), A_sym.y());

    CHECK_EQ(B_sym.x(), 5);
    CHECK_EQ(B_sym.y(), 0);
}

TEST_CASE("Line-Line Symetry")
{
}