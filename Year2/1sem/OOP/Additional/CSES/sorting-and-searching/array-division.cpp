#include <bits/stdc++.h>
using namespace std;

long long nums[200001];

bool canDivide(size_t n, int maxK, long long maxSum)
{
    long long curSum = 0ll;
    int curK = 1;
    for (int i = 0; i < n; ++i)
    {
        if (curSum + nums[i] <= maxSum)
        {
            curSum += nums[i];
        }
        else
        {
            curSum = nums[i];
            curK++;
            if (curK > maxK)
                return false;
        }
    }
    return true;
}

int main()
{
    map<long long, int> curMap;

    long long total = 0ll;

    size_t n, k;
    cin >> n >> k;

    for (size_t i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    long long low, up, mid;
    up = accumulate(nums, nums + n, 0ll);
    low = *max_element(nums, nums + n);

    while (up - low > 1)
    {

        mid = low + (up - low) / 2;

        if (canDivide(n, k, mid))
            up = mid;
        else
            low = mid;
    }

    cout << (canDivide(n, k, low) ? low : up) << '\n';
}