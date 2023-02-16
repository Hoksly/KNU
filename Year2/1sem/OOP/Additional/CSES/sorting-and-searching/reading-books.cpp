#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    long long sum = 0ll, maxEl = INT64_MIN, cur;

    for (int i = 0; i < n; ++i)
    {
        cin >> cur;
        sum += cur;
        if (cur > maxEl)
            maxEl = cur;
    }
    cout << max(sum, maxEl * 2ll);
}