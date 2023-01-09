#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();

        for (int i = 0; i < n - 2; ++i)
        {
            if (i > 0 && (nums[i] == nums[i - 1]))
                continue;

            int leftPointer = i + 1;
            int rightPointer = n - 1;

            while (leftPointer < rightPointer)
            {
                int threesome = nums[i] + nums[leftPointer] + nums[rightPointer];
                if (threesome > 0)
                    rightPointer--;
                else if (threesome < 0)
                    leftPointer++;
                // -1,0,1,2,-1,-4
                // -4 -1 -1 0 1 2
                else
                {
                    ans.push_back({nums[i], nums[leftPointer], nums[rightPointer]});

                    while (((leftPointer < rightPointer) && nums[leftPointer] == nums[leftPointer + 1]))
                    {
                        leftPointer++;
                    }
                    leftPointer++;
                }
            }
        }

        return ans;
    }
};