/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, 
compute how much water it can trap after raining.

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6

Input: height = [4,2,0,3,2,5]
Output: 9




    n == height.length
    1 <= n <= 2 * 10^4
    0 <= height[i] <= 10^5


*/
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int trap(vector<int>& height) {
        int peakHeight = height[0], peakIndex = 0;
        bool isGrowing = true;
        int heightMaxIndex = height.size() - 1, trappedWaterTotal = 0;
        

        for(int i = 0; i < heightMaxIndex; ++i)
        {
            if (height[i+1] > height[i])
            {
                isGrowing = true;
                trappedWaterTotal += cutSub(peakHeight, height[i]);
            }
            else
            {
                if(isGrowing)
                {
                    trappedWaterTotal -= cutSub(peakHeight, height[i]) * (i - peakIndex);
                    peakHeight = height[i];
                    peakIndex = i; 
                }
                else
                {
                    trappedWaterTotal += cutSub(peakHeight, height[i]);
                }

                isGrowing = false;
            }
        }

        return trappedWaterTotal;
    }

    inline int cutSub(const int a, const int b)
    {
        return (a > b)? a-b: 0;
    }
};
