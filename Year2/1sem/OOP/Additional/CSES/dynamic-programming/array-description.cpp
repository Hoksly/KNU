
#include <bits/stdc++.h>

using namespace std;
const long long mod = 1000000007ll;
int main()
{

    int n, m;
    cin >> n >> m;
    vector<long long> nums(n);
    vector<vector<long long>> mapping(n, vector<long long>(m + 1, 0ll));

    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    if (nums[0] == 0)
    {
        fill(mapping[0].begin() + 1, mapping[0].end(), 1);
    }
    else
    {
        mapping[0][nums[0]] = 1;
    }
    for (int i = 1; i < n; ++i)
    {
        if (nums[i] != 0)
        {
            mapping[i][nums[i]] = mapping[i - 1][nums[i]];
            if (nums[i] < m)
                mapping[i][nums[i]] += mapping[i - 1][nums[i] + 1];
            if (nums[i] > 1)
                mapping[i][nums[i]] += mapping[i - 1][nums[i] - 1];
            mapping[i][nums[i]] %= mod;
        }
        else
        {
            for (int j = 1; j < m + 1; ++j)
                mapping[i][j] = mapping[i - 1][j];
            for (int j = 1; j < m; ++j)
            {
                mapping[i][j] += mapping[i - 1][j + 1];
                mapping[i][j] %= mod;
            }
            mapping[i][m] = mapping[i - 1][m];
            for (int j = 2; j < m + 1; ++j)
            {
                mapping[i][j] += mapping[i - 1][j - 1];
                mapping[i][j] %= mod;
            }
        }
    }

    cout << accumulate(mapping[n - 1].begin(), mapping[n - 1].end(), 0ll) % mod << endl;
}
