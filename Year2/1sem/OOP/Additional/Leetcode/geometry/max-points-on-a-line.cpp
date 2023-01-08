#include <bits/stdc++.h>
using namespace std;
/*
We use direction counter here to find max points on each line.
O(n^2) * log(max(coord))
log is for GCD

*/
class Solution
{
public:
    inline size_t normalizeAndConvert(int x, int y)
    {
        int gcd = __gcd(x, y);
        x /= gcd;
        y /= gcd;

        if (x < 0)
        {
            x = -x;
            y = -y;
        }
        else if (x == 0)
            y = (y > 0) ? y : -y;

        return (size_t)x << 32 | (unsigned int)y;
    }

    int maxPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        unordered_map<size_t, int> directionCounter;
        int maxColinear = 1, tmp;
        unordered_map<size_t, int>::iterator maxElement;

        for (int i = 0; i < n; ++i)
        {
            directionCounter.clear();

            for (int j = i + 1; j < n; ++j)
            {

                size_t hash = normalizeAndConvert(
                    points[i][0] - points[j][0],
                    points[i][1] - points[j][1]);
                directionCounter[hash] += 1;
            }
            maxElement = max_element(
                directionCounter.begin(), directionCounter.end(), [](const pair<size_t, int> &a, const pair<size_t, int> &b) -> bool
                { return a.second < b.second; });
            tmp = (maxElement != directionCounter.end()) ? maxElement->second : -1;

            maxColinear = max(tmp + 1, maxColinear);
        }
        return maxColinear;
    }
};