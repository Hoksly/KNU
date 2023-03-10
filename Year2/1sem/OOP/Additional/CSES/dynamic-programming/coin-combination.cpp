#include <bits/stdc++.h>

using namespace std;

const long mod = 1000000007l;

int main()
{
    long n, target, x;
    cin >> n >> target;

    long *sums = new long[target + 1];
    long *coins = new long[n];

    for (int i = 0; i < n; ++i)
    {
        cin >> coins[i];
    }
    fill(sums + 1, sums + target + 1, 0l);
    sums[0] = 1;
    for (int i = 1; i < target + 1; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i - coins[j] > -1)
            {
                sums[i] += sums[i - coins[j]];
                sums[i] %= mod;
            }
        }
    }
    cout << sums[target] << '\n';
}
