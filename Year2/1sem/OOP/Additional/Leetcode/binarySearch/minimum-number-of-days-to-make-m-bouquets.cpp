/*
You are given an integer array bloomDay, an integer m and an integer k.

You want to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.

The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.

Return the minimum number of days you need to wait to be able to make m bouquets from the garden. If it is impossible to make m bouquets return -1.


Main idea:
    We create a function, that answer the question "can we create at least m bouquets with k flowers in each in day days", and then we use
    binary search to find minimum possible day so fucntion return true

    We return -1 only when we need use more flowers than we have

    min Bound - 1 day
    max Bound - max(bloomay)

*/

#include <bits/stdc++.h>

using std::vector;

class Solution
{
public:
    int minDays(vector<int> &bloomDay, int m, int k)
    {
        if ((size_t)m * (size_t)k > bloomDay.size())
            return -1;
        if ((size_t)m * (size_t)k == bloomDay.size())
            return *std::max_element(bloomDay.begin(), bloomDay.end());

        int minDays = *std::min_element(bloomDay.begin(), bloomDay.end());
        int maxDays = *std::max_element(bloomDay.begin(), bloomDay.end());
        int midDays;
        while (maxDays - minDays > 1)
        {
            midDays = (maxDays + minDays) / 2;
            if (canMakeBouquets(bloomDay, midDays, m, k))
            {
                maxDays = midDays;
            }
            else
                minDays = midDays;
        }

        return canMakeBouquets(bloomDay, minDays, m, k) ? minDays : maxDays;
    }

    inline bool canMakeBouquets(vector<int> &bloomDay, int day, int m, int k)
    {
        int totalCreated = 0, n = bloomDay.size(), flowersInBoquet = 0;

        for (int i = 0; i < n; ++i)
        {
            if (bloomDay[i] <= day)
            {
                flowersInBoquet += 1;
                if (flowersInBoquet == k)
                {
                    totalCreated += 1;
                    flowersInBoquet = 0;
                }
            }
            else
                flowersInBoquet = 0;
        }

        return totalCreated >= m;
    }
};