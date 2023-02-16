#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio();
    cin.tie(0);
    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> nums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i].first;
        nums[i].second = i + 1;
    }

    sort(nums.begin(), nums.end());

    int rightPtr, leftPtr, target;
    for (int i = 0; i < n - 2; ++i)
    {
        leftPtr = i + 1;
        rightPtr = n - 1;
        target = x - nums[i].first;
        while (leftPtr < rightPtr)
        {
            if (nums[leftPtr].first + nums[rightPtr].first == target)
            {
                cout << nums[i].second << ' ' << nums[leftPtr].second << ' ' << nums[rightPtr].second << '\n';
                return 0;
            }
            else if (nums[leftPtr].first + nums[rightPtr].first > target)
            {
                rightPtr--;
            }
            else
            {
                leftPtr++;
            }
        }
    }
    cout << "IMPOSSIBLE" << '\n';
}