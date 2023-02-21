#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n, target, x;
    cin >> n >> target;

    long long *sums = new long long[target + 1];
    long long *coins = new long long[n];

    for (int i = 0; i < n; ++i)
    {
        cin >> coins[i];
    }
    fill(sums + 1, sums + target + 1ll, LONG_LONG_MAX - 1ll);
    sums[0] = 0ll;
    for (int i = 1; i < target + 1; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i - coins[j] > -1)
            {
                sums[i] = min(sums[i], sums[i - coins[j]] + 1);
            }
        }
    }
    cout << ((sums[target] == LONG_LONG_MAX - 1) ? -1 : sums[target]) << endl;
}