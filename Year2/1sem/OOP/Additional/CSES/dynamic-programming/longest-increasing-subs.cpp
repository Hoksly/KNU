#include <bits/stdc++.h>

using namespace std;

int longestIncreasing(vector<int> &a)
{

    vector<int> dp;

    for (int i : a)
    {

        int pos = lower_bound(dp.begin(), dp.end(), i) - dp.begin();

        if (pos == dp.size())
        {

            dp.push_back(i);
        }
        else
        {

            dp[pos] = i;
        }
    }

    return dp.size();
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    cout << longestIncreasing(nums) << endl;
}