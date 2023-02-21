#include <bits/stdc++.h>
using namespace std;

const long mod = 1000000007l;
int main()
{
    ios::sync_with_stdio();
    cin.tie(0);

    int n;
    cin >> n;
    long *arr = new long[n + 1];
    arr[0] = 1;

    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < 7; ++j)
        {
            if (i - j < 0)
                break;

            arr[i] += arr[i - j];
            arr[i] %= mod;
        }
    }

    cout << arr[n] << endl;
}