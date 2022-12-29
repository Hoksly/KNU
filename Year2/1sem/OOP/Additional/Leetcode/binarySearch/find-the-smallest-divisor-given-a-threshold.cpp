/*
Given an array of integers nums and an integer threshold, we will choose a positive integer divisor, divide all the array by it,
and sum the division's result. Find the smallest divisor such that the result mentioned above is less than or equal to threshold.

Each result of the division is rounded to the nearest integer greater than or equal to that element. (For example: 7/3 = 3 and 10/2 = 5).

The test cases are generated so that there will be an answer.


Main idea:
    we define a fundtion getDividedSum, that return a sum of a division's results of number in vector nums by particular divider div,
    then we can use a binary search to find the smallest divider, using which, our sum will be less or equal to threshold

*/

#include <vector>

using std::vector;

class Solution
{
public:
    int smallestDivisor(vector<int> &nums, int threshold)
    {
        long minDiv = 1, maxDiv = -1, n = nums.size(), midDiv;

        for (int i = 0; i < n; ++i)
        {
            if (nums[i] > maxDiv)
                maxDiv = nums[i];
        }

        while (maxDiv - minDiv > 1)
        {
            midDiv = (maxDiv + minDiv) / 2;

            if (getDividedSum(nums, midDiv) <= threshold)
            {
                maxDiv = midDiv;
            }
            else
            {
                minDiv = midDiv;
            }
        }

        return (getDividedSum(nums, minDiv) > threshold) ? maxDiv : minDiv;
    }

private:
    int getDividedSum(vector<int> &nums, int div)
    {

        int res = 0;
        for (int number : nums)
        {

            res += ((number / div) + ((number % div) ? 1 : 0));
        }

        return res;
    }
};
