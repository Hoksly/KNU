#include <bits/stdc++.h>

using namespace std;

inline bool isStrike(pair<int, int> K1, pair<int, int> K2)
{
    return (K1.first - 1 == K2.first && K1.second == K2.second - 2);
}