#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    int countKDifference(vector<int> &nums, int k)
    {
        int res = 0, n = nums.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                    res += (nums[i] + nums[j] + nums[k] == 0)1 : 0;
    }
};

int main()
{
}