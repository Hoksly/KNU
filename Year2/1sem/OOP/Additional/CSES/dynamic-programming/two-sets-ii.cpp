#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, mod = 1e9 + 7;
    cin >> n;

    int S = n * (n + 1) / 2;
    int s = S / 2;

    vector<vector<int>> dp(n + 1, vector<int>(s + 1, 0));
    if (S % 2)
    {
        cout << 0;
        return 0;
    }
    dp[0][0] = 1;

    for (int sum = 0; sum <= s; sum++)
    {

        for (int i = 1; i < n; i++)
        {
            dp[i][sum] = dp[i - 1][sum];
            if (sum - i >= 0)
            {
                dp[i][sum] = dp[i - 1][sum] + dp[i - 1][sum - i];

                dp[i][sum] %= mod;
            }
        }
    }
    cout << dp[n - 1][s] << endl;

    return 0;
}