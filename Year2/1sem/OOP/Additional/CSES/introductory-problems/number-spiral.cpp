#include <bits/stdc++.h>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    cin.tie(NULL)->sync_with_stdio();

    int t;
    long long x, y;
    cin >> t;
    while (t--)
    {
        cin >> y >> x;

        if (x >= y)
        {
            if (x % 2)
            {
                cout << x * x - y + 1LL << '\n';
            }
            else
            {
                cout << (x - 1LL) * (x - 1LL) + y << '\n';
            }
        }
        else
        {
            if (y % 2)
            {
                cout << (y - 1LL) * (y - 1LL) + x << '\n';
            }
            else
            {
                cout << y * y - x + 1LL << '\n';
            }
        }
    }
}