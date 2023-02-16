#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    sort(nums.begin(), nums.end());

    int cur = nums[0], total = 1;
    for (int i = 1; i < n; ++i)
    {
        if (cur != nums[i])
        {
            ++total;
            cur = nums[i];
        }
    }

    cout << total << '\n';
}