#include "vlib/victor.hpp"
#include <iostream>
#include "doctest/doctest/doctest.h"

using namespace std;
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

TEST_CASE("Please work")
{
    int a = 5;

    CHECK(a == 5);
}

int main()
{
}
