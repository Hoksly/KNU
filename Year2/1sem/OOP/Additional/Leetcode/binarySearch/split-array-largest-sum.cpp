/*
Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.

Return the minimized largest sum of the split.

A subarray is a contiguous part of the array.

The canSplit function is strange and it works, but I don't know why...

*/

#include <bits/stdc++.h>

using std::vector;

class Solution
{
public:
    int splitArray(vector<int> &nums, int k)
    {
        int minBound, maxBound, midBound;
        minBound = *std::max_element(nums.begin(), nums.end());
        maxBound = std::accumulate(nums.begin(), nums.end(), 0);

        while (maxBound - minBound > 0)
        {
            midBound = (maxBound + minBound) / 2;
            if (canSplit(nums, midBound, k))
                maxBound = midBound;
            else
                minBound = midBound + 1;
        }
        return minBound;
    }

    inline bool canSplit(vector<int> &nums, int maxCapacity, int arraysTotal)
    {
        int arrays = 1, accumulated = 0;
        for (int number : nums)
        {
            accumulated += number;
            if (accumulated > maxCapacity)
            {
                arrays += 1;
                accumulated = number;
                if (arrays > arraysTotal)
                    return false;
            }
        }

        return true;
    }
};
