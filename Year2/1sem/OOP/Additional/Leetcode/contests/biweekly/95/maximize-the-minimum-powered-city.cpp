#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    long long maxPower(vector<int> &stations, int r, int k)
    {
        vector<long long> stationsCopy(stations.size(), 0);

        long long _r = r, _k = k;
        vector<long long> cache(stations.size(), 0);

        long long n = stations.size();

        long long initVal, minVal, maxVal, midVal;
        initVal = 0;

        for (long long i = 0; i < n; ++i)
            stationsCopy[i] = (stations[i]);

        for (long long i = 0; i < _r + 1; ++i)
            initVal += stations[i];

        minVal = 0;
        maxVal = LLONG_MAX;

        while (minVal < maxVal)
        {

            midVal = minVal + (maxVal - minVal) / 2;

            if (valid(stationsCopy, r, k, midVal, initVal, cache))
                minVal = midVal + 1;

            else
                maxVal = midVal - 1;
        }

        return (valid(stationsCopy, _r, _k, maxVal, initVal, cache) ? maxVal : maxVal - 1);
    }

    bool valid(const vector<long long> &powers, long long r, long long k, long long minPower, long long &initVal, vector<long long> &cache)
    {

        fill(cache.begin(), cache.end(), 0);

        long long currPower = initVal, used = 0;
        long long n = powers.size();

        for (long i = 0; i < powers.size(); i++)
        {

            if (currPower < minPower)
            {
                k -= (minPower - currPower);

                cache[min(i + r, n - 1)] += minPower - currPower;
                currPower = minPower;
            }
            if (k < 0)
            {

                return false;
            }

            if (i + r + 1 < n)
                currPower += powers[i + r + 1] + cache[i + r + 1];

            if (i >= r)
                currPower -= (powers[i - r] + cache[i - r]);
        }

        return true;
    }
};
int main()
{
    Solution s;
    vector<int> nums = {1, 2, 4, 5, 0};
    cout << s.maxPower(nums, 1, 2) << endl;
}