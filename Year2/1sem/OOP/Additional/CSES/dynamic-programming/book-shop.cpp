#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;

    vector<int> arr(x + 1, INT_MIN);
    vector<pair<int, int>> nums(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i].first;
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i].second;
    }

    arr[0] = 0;

    for (int k = 0; k < n; k++)
    {
        for (int i = x; i > -1; --i)
        {

            if (arr[i] != INT_MIN && i + nums[k].first <= x)
            {
                arr[i + nums[k].first] = max(arr[i + nums[k].first], arr[i] + nums[k].second);
            }
        }
    }

    cout << *max_element(arr.begin(), arr.end()) << endl;
}