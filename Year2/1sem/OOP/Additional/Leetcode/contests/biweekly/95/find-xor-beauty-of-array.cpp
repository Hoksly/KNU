#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

class Solution
{
public:
    int xorBeauty(vector<int> &nums)
    {
        int beauty = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            beauty ^= nums[i];
        }
        return beauty;
    }
};