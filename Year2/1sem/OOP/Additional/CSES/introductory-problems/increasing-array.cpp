#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio();

    int cur, prev, n;
    long moves = 0;

    cin >> n;
    cin >> prev;

    for (int i = 0; i < n - 1; ++i)
    {
        cin >> cur;
        if (cur < prev)
        {
            moves += (prev - cur);
            cur = prev;
        }
        prev = cur;
    }
    cout << moves << endl;
}