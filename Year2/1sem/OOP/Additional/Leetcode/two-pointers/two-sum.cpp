#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        int n = nums.size();
        vector<int> ans;
        unordered_map<int, int> hashTable;
        for (int i = 0; i < n; i++)
        {
            if (hashTable.count(target - nums[i]))
            {
                ans.push_back(hashTable[target - nums[i]]);
                ans.push_back(i);
            }
            hashTable[nums[i]] = i;
        }
        return ans;
    }
};

int main()
{
    vector<int> v = {2,
                     7,
                     11,
                     15};

    Solution s;
    vector<int> res = s.twoSum(v, 9);
    cout << res[0] << ' ' << res[1] << endl;
}