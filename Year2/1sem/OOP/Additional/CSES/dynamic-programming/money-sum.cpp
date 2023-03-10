#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.sync_with_stdio();
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> coins(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> coins[i];
    }
    bitset<100001> poss;

    poss[0] = true;
    int maxEl = 0, tmpMx = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 100000 - coins[i]; j > -1; --j)
        {

            poss[j + coins[i]] = poss[j + coins[i]] | poss[j];
        }
    }
    cout << poss.count() - 1 << '\n';
    for (int i = 1; i < 100001; ++i)
    {
        if (poss[i])
            cout << i << ' ';
    }

    cout << '\n';
}