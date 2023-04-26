#include "doctest.h"

/*
TEST_CASE("Vector initialization")
{
    victor<int> A(10);
    A[3] = 100;
    CHECK_EQ(A[3], 100);
    CHECK_THROWS_AS(victor<int> A(-1), std::bad_alloc);
}

TEST_CASE("Pushing and popping elements in vector")
{
    victor<int> V;
    V.push_back(10);

    CHECK_EQ(V[0], 10);
    CHECK_EQ(V.size(), 1);

    CHECK_EQ(10, V.pop_back());

    CHECK_EQ(V.size(), 0);
    CHECK_THROWS_AS(V.pop_back(), std::out_of_range);
}

TEST_CASE("Inserting elem")
{
    victor<int> V;

    V.push_back(0);
    V.push_back(2);
    V.insert(1, 1);

    CHECK(V.str().size() == 5);
    CHECK(V.size() == 3);
    CHECK(V.str() == "0 1 2");
}

TEST_CASE("Insert Sort")
{
}

*/