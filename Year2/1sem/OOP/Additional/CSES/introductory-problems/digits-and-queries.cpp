#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int t;
    ll k;
    cin.tie(NULL)->sync_with_stdio();
    // freopen("input.txt", "r", stdin);
    cin >> t;
    while (t--)
    {
        cin >> k;
        ll cur = 1;
        ll n = 9LL;
        ll i = 1LL;

        while (k > n * i)
        {
            k -= n * i;
            n *= 10LL;
            cur *= 10LL;
            i++;
        }
        k--;

        cur += k / i;

        k %= (i);

        for (int q = i - k - 1; q > 0; --q)
        {
            cur /= 10LL;
        }

        cout << cur % 10 << '\n';
    }
}