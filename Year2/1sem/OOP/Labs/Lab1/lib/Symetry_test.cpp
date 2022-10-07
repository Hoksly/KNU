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

    CHECK_EQ(l1_2_sym.b(), -3);
    CHECK_EQ(l1_2_sym.k(), 1);
    CHECK_EQ(l1_2_sym.angle(), M_PI_4);

    // perpendicular
    Line l1_3_sym = s.symetry(l1, l3);

    REQUIRE_EQ(l1_3_sym.b(), doctest::Approx(5));
    REQUIRE_EQ(l1_3_sym.k(), doctest::Approx(-1));
    REQUIRE_EQ(l1_3_sym.angle(), doctest::Approx(-M_PI_4));

    Line l4(Point(1, 7), Point(4, 35));

    Line l1_4_sym = s.symetry(l1, l4);

    REQUIRE_EQ(l1_4_sym.k(), doctest::Approx(0.107143));
    REQUIRE_EQ(l1_4_sym.b(), doctest::Approx(0.25));
}

TEST_CASE("Triangle-Line symetry")
{
    Line l1(Point(1, 1), Point(5, 5));
    Symetry s;
    Triangle T(Point(1, 1), Point(5, 0), Point(10, 15));

    Triangle T_sym = s.symetry(T, l1);

    Triangle T_check = Triangle(Point(0, 5), Point(15, 10), Point(1, 1));
    // std::cout << T_check.str() << std::endl;
    // std::cout << T_sym.str() << std::endl;

    CHECK(T_sym.has_same_points(T_check));
}

TEST_CASE("Point inversion")
{
    Symetry s;

    Point A(1, 1);
    Point B(3, 3);
    Point D(0.5, 0.5);
    Point Center(0, 0);

    Circle C(Point(0, 0), 1);

    Point A_inv = s.inversion(A, C);
    Point B_inv = s.inversion(B, C);
    Point D_inv = s.inversion(D, C);

    REQUIRE_EQ(C.O().distance_to(A) * C.O().distance_to(A_inv), doctest::Approx(pow(C.r(), 2)));
    REQUIRE_EQ(C.O().distance_to(B) * C.O().distance_to(B_inv), doctest::Approx(pow(C.r(), 2)));
    REQUIRE_EQ(C.O().distance_to(D) * C.O().distance_to(D_inv), doctest::Approx(pow(C.r(), 2)));
}

TEST_CASE("Triangle inversion")
{
    Symetry s;
    Circle C(Point(0, 0), 1);
    Triangle T(Point(1, 1), Point(5, 5), Point(10, 0));

    Triangle T_inv = s.inversion(T, C);

    REQUIRE_EQ(C.O().distance_to(T.A()) * C.O().distance_to(T_inv.A()), doctest::Approx(pow(C.r(), 2)));

    REQUIRE_EQ(C.O().distance_to(T.C()) * C.O().distance_to(T_inv.C()), doctest::Approx(pow(C.r(), 2)));

    REQUIRE_EQ(C.O().distance_to(T.B()) * C.O().distance_to(T_inv.B()), doctest::Approx(pow(C.r(), 2)));
}

TEST_CASE("Line inversion")
{
    Symetry s;

    Line l1(1, 0);
    Line l2(1, 0.5);
    Line l3(1, 100);

    Circle C(Point(0, 0), 1);

    // Line l1_inv = boost::get<Line>(s.inversion(l1, C));
    Circle l2_inv = boost::get<Circle>(s.inversion(l2, C));
    // Circle l3_inv = boost::get<Circle>(s.inversion(l3, C));

    // std::cout << l1_inv.str() << std::endl;
    std::cout << l2_inv.str() << std::endl;
    // std::cout << l3_inv.str() << std::endl;

    // Point point_on_inverted_1 = l1_inv.random_point();
    Point point_on_inverted_2 = l2_inv.random_point();
    // Point point_on_inverted_3 = l3_inv.random_point();

    // std::cout << point_on_inverted_1.str() << std::endl;
    std::cout << point_on_inverted_2.str() << std::endl;
    // std::cout << point_on_inverted_3.str() << std::endl;

    // std::cout << s.inversion(point_on_inverted_1, C).str() << std::endl;
    std::cout << s.inversion(point_on_inverted_2, C).str() << std::endl;
    // std::cout << s.inversion(point_on_inverted_3, C).str() << std::endl;

    // CHECK(l1.passes_through(s.inversion(point_on_inverted_1, C)));

    CHECK(l2.passes_through(s.inversion(point_on_inverted_2, C)));

    // CHECK(l3.passes_through(s.inversion(point_on_inverted_3, C)));
}

TEST_CASE("Circle inversion")
{
}