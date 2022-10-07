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
    Symetry s;

    Line l1(Point(1, 1), Point(5, 5));
    Line l2(Point(1, 4), Point(5, 8));
    Line l3(Point(5, 0), Point(0, 5));

    // paralels
    Line l1_2_sym = s.symetry(l1, l2);

    std::cout << l1_2_sym.str() << std::endl;
    CHECK_EQ(l1_2_sym.b(), -3);
    CHECK_EQ(l1_2_sym.k(), 1);
    CHECK_EQ(l1_2_sym.angle(), M_PI_4);

    // perpendicular
    Line l1_3_sym = s.symetry(l1, l3);

    CHECK_EQ(l1_3_sym.b(), 5);
    CHECK_EQ(l1_3_sym.k(), -1);
    CHECK_EQ(l1_3_sym.angle(), -M_PI_4);

    Line l4(Point(1, 7), Point(4, 35));

    Line l1_4_sym = s.symetry(l1, l4);
    std::cout << l1_4_sym.str() << std::endl;

    REQUIRE_EQ(l1_4_sym.k(), doctest::Approx(0.107143));
    REQUIRE_EQ(l1_4_sym.b(), doctest::Approx(0.25));
}

TEST_CASE("Triangle-Line symetry")
{
    Line l1(Point(1, 1), Point(5, 5));

    Triangle(Point(1, 1), Point(5, 0), Point(10, 15));
}