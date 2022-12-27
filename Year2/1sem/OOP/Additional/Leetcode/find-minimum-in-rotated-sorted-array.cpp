/*
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:

    [4,5,6,7,0,1,2] if it was rotated 4 times.
    [0,1,2,4,5,6,7] if it was rotated 7 times.

Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums of unique elements, return the minimum element of this array.

You must write an algorithm that runs in O(log n) time.

*/
#include <vector>
#include <iostream>

using std::vector;

class Solution
{
public:
    int findMin(vector<int> &nums)
    {
        int leftBound = 0, rightBound = nums.size() - 1, mid;

        while (rightBound - leftBound != 1)
        {

            mid = (rightBound + leftBound) / 2;

            if (nums[mid] < nums[rightBound])
            {
                rightBound = mid;
            }
            else
                leftBound = mid;
        }

        return std::min(nums[leftBound], nums[rightBound]);
    }
};

int main()
{
    vector<int> A = {4, 5, 6, 7, 0, 1, 2};
    Solution s;
    s.findMin(A);
}