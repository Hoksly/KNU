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
        int leftPointer = 0, rightPointer = height.size()-1;
        int leftMax = -1, rightMax = -1;
        int trappedTotal = 0;

        while (leftPointer <= rightPointer)
        {
            if (height[leftPointer] <= height[rightPointer])
            {
                if (height[leftPointer] > leftMax)
                    leftMax = height[leftPointer];
                else
                {
                    trappedTotal += leftMax - height[leftPointer];
                }
                leftPointer++;
            }

            else
            {
                if (height[rightPointer] > rightMax)
                    rightMax = height[rightPointer];
                else
                {
                    trappedTotal += rightMax - height[rightPointer];
                } 
                rightPointer--;
            }
        }
        return trappedTotal;
        
    }
};
