#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> nums(n);

    for (long long &i : nums)
        cin >> i;

    sort(nums.begin(), nums.end());

    long long median = nums[n / 2];

    long long ans = 0;
    for (const long long &x : nums)
    {
        ans += llabs(x - median);
    }
    cout << ans << endl;
}