#include "vlib/victor.hpp"
#include <iostream>
#include "vlib/sort.hpp"
using namespace std;
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

int main()
{

    victor<int> v(10);
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(10 - i);
    }
    cout << v << endl;
    v.sort();

    cout << v << endl;
}
