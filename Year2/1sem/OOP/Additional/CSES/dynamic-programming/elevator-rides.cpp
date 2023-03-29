#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    int n, maxWeight;
    cin >> n >> maxWeight;
    vector<int> weights(n);

    for (int i = 0; i < n; ++i)
        cin >> weights[i];
    int limit = 1 << n;

    vector<pair<ll, ll>> dp(limit);
    pair<ll, ll> best;
    dp[0] = {1, 0};
    for (int mask = 1; mask < limit; ++mask)
    {
        best = {INT_MAX, INT_MAX};
        for (int i = 0; i < n; ++i)
        {
            if (((1 << i) & mask) == 0)
            {
                continue;
            }
            auto res = dp[(1 << i) ^ mask];
            if (res.second + weights[i] <= maxWeight)
            {
                res.second += weights[i];
            }
            else
            {
                res.first += 1;
                res.second = weights[i];
            }
            best = min(best, res);
        }
        dp[mask] = best;
    }

    cout << dp[limit - 1].first << endl;
}