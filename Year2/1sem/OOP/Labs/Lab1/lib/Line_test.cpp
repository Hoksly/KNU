#include "/home/hoksly/Github/KNU/Year2/1sem/OOP/Labs/Lab1/doctest/doctest/doctest.h"
#include "Line.hpp"

TEST_CASE("Line init")
{
    Line l1(Point(0, 0), Point(0, 5));

    CHECK(l1.angle() == M_PI_2);
    CHECK(l1.b() == 0);

    Line l2(Point(1, 1), Point(5, 5));

    CHECK(l2.k() == 1);
    CHECK(l2.angle() == M_PI_4);
    CHECK(l2.b() == 0);

    Line l3(Point(4, 0), Point(5, 0));

    CHECK(l3.k() == 0);
    CHECK(l3.b() == 0);
    CHECK(l3.angle() == 0);
}

TEST_CASE("Line inteception")
{
    Line l1(Point(0, 0), Point(0, 5));
    Line l2(Point(1, 1), Point(5, 5));
    Line l3(Point(4, 0), Point(5, 0));

    std::vector<Point> pts = l1.intercept(l3);
    CHECK(pts.size() == 1);
    CHECK(l1.intercept(l3)[0] == Point(0, 0));

    pts = l1.intercept(l2);
    CHECK(pts.size() == 1);
    CHECK(pts[0] == Point(0, 0));

    pts = l2.intercept(l3);
    CHECK(pts.size() == 1);
    CHECK(pts[0] == Point(0, 0));
}

TEST_CASE("Line normal vector")
{
    Line l1(Point(0, 0), Point(0, 5));
    Line l2(Point(1, 1), Point(5, 5));

    CHECK(l1.normal_vecor() == Vector(1, 0));
    CHECK(l2.normal_vecor() == Vector(1, -1));
}

TEST_CASE("Line passes through")
{
    Line l1(Point(0, 0), Point(0, 5));
    Line l2(Point(1, 1), Point(5, 5));

    CHECK(l1.passes_through(Point(0, 2.5)));
    CHECK_FALSE(l1.passes_through(Point(12, 332)));

    CHECK(l2.passes_through(Point(2.5, 2.5)));
    CHECK_FALSE(l2.passes_through(Point(12, 332)));
}

TEST_CASE("Line-Circle interception")
{
    Circle C(Point(0, 0), 2);

    Line l1(Point(1, 1), Point(5, 5));  // 2
    Line l2(Point(-5, 0), Point(0, 5)); // 0
    Line l3(Point(5, 2), Point(7, 2));  // 1
    Line l4(Point(1, 1), Point(1, 5));  // 2

    std::vector<Point> points;
    points = l1.intercept(C);
    CHECK_EQ(points.size(), 2);

    points = l2.intercept(C);
    CHECK_EQ(points.size(), 0);

    points = l3.intercept(C);
    CHECK_EQ(points.size(), 1);

    points = l4.intercept(C);
    CHECK_EQ(points.size(), 2);
}