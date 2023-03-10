#include <bits/stdc++.h>

using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<long long> nums(n);
    vector<vector<long long>> dp(n, vector<long long>(n));

    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
        dp[i][i] = nums[i];
    }

    for (int i = n - 1; i > -1; --i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
        }
    }
    cout << (accumulate(nums.begin(), nums.end(), 0ll) + dp[0][n - 1]) / 2ll;
}