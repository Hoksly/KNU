#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] < 1 || nums[i] > n)
                nums[i] = n + 1;
        }

        // now all numbers in array from 1 to n+1

        // so we can use array as hash-table for itself
        // where if nums[x-1] is negative means that x is present in array
        // also we ignore n+1
        int cur;
        for (int i = 0; i < n; ++i)
        {
            cur = abs(nums[i]);
            if (cur > n)
                continue;
            if (nums[cur - 1] > 0)
                nums[cur - 1] = -nums[cur - 1];
        }
        // so now we can simply find that first missing number just because it will be positive
        for (int i = 0; i < n; i++)
        {
            if (nums[i] > 0)
                return i + 1;
        }
        // or if all negative we return n+1
        return n + 1;
    }
};

int main()
{
    Solution s;
    vector<int> test = {3, 4, -1, 1, 2, 7, 8};

    cout << s.firstMissingPositive(test) << endl;
}