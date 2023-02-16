#include <bits/stdc++.h>

using namespace std;

bool canProduce(vector<long long> &times, long long time, long long requiredProducts)
{
    long long totalProducts = 0;
    for (long long machineTime : times)
    {
        totalProducts += time / machineTime;
    }
    return requiredProducts <= totalProducts;
}

int main()
{
    long long n, t;
    cin >> n >> t;
    vector<long long> times(n);
    for (long long i = 0; i < n; ++i)
    {
        cin >> times[i];
    }

    long long low, up, mid;
    low = 0;
    up = *min_element(times.begin(), times.end()) * t;

    while (low < up - 1)
    {
        mid = low + (up - low) / 2;
        if (canProduce(times, mid, t))
        {
            up = mid;
        }
        else
        {
            low = mid;
        }
    }

    cout << (canProduce(times, low, t) ? low : up);
}