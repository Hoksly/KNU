/*
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49

Input: height = [1,1]
Output: 1


*/

#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int leftPointer = 0, rightPointer = height.size() - 1;
        int containerHeight = min(height[leftPointer], height[rightPointer]);
        
        int maxS = containerHeight * (rightPointer - leftPointer), heightsCount = height.size();


        while(rightPointer > leftPointer)
        {
            containerHeight = min(height[rightPointer], height[leftPointer]);
            maxS = max(maxS, containerHeight * (rightPointer-leftPointer));
            

            while(rightPointer > 0 && containerHeight >= height[rightPointer]) {rightPointer--;}
            while (leftPointer < heightsCount-1 && containerHeight >= height[leftPointer]) {++leftPointer;}
        
        }

        return maxS;
        
    }
};