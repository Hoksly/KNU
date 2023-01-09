#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int lowPointer = 0, midPointer = 0, highPointer = nums.size() - 1;

        while (midPointer <= highPointer)
        {
            if (nums[midPointer] == 0)
            {
                swap(nums[midPointer], nums[lowPointer]);
                midPointer++;
                lowPointer++;
            }
            else if (nums[midPointer] == 1)
                midPointer++;
            else
            {
                swap(nums[midPointer], nums[highPointer]);
                highPointer--;
            }
        }
    }
};