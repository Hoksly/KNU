#include <vector>
#include <iostream>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {

        int l = 0, r = numbers.size() - 1;
        vector<int> ret(2);

        while (r - l > 1)
        {
            if (numbers[l] + numbers[r] == target)
            {
                ret[0] = l;
                ret[1] = r;
                return ret;
            }
            if (numbers[l] + numbers[r] > target)
                r--;
            else
                l++;
        }
        ret[0] = l;
        ret[1] = r;
        return ret;
    }
};

int main()
{
    vector<int> V = {2, 7, 11, 15};
    Solution s;
    s.twoSum(V, 9);
}