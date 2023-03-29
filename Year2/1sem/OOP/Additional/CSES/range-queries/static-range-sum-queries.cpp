#include <bits/stdc++.h>

using namespace std;

long long sums[200001];

int main()
{
    cin.sync_with_stdio();

    int n, q, l, r;
    long long cur;
    cin >> n >> q;
    sums[0] = 0;
    for (int i = 1; i < n + 1; ++i)
    {
        cin >> cur;
        sums[i] = sums[i - 1] + cur;
    }

    for (int i = 0; i < q; ++i)
    {
        cin >> l >> r;
        cout << sums[r] - sums[l - 1] << '\n';
    }
}
