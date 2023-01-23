#include <iostream>
#include <cmath>
using namespace std;

bool can(int a)
{

    int a_cp = a;
    int x = 1;
    int y = 1;

    while (a % 2 == 0 && a > 0)
    {

        a /= 2;
        x *= 2;
        y *= 2;
    }
    --a;

    if (a == 0 && x != 1)
    {

        return true;
    }

    while (a % 2 == 0 && a > 0)
    {

        x *= 2;
        a /= 2;
    }
    return a_cp == x + y;
}

class Solution
{
public:
    bool isReachable(int targetX, int targetY)
    {
        while (targetX % 2 == 0)
            targetX /= 2;
        while (targetY % 2 == 0)
            targetY /= 2;
        return __gcd(targetX, targetY) == 1;
    }
};
