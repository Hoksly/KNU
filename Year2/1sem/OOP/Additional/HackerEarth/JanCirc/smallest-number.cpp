#include <bits/stdc++.h>
using namespace std;
int main()
{
    cin.tie(NULL)->sync_with_stdio();

    int t, n;
    cin >> t;
    vector<int> nums;
    while (t--)
    {
        cin >> n;
        nums.resize(n);
        for (int &a : nums)
            cin >> a;

        sort(nums.begin(), nums.end());

        int nonPresent = 0;
    }
}