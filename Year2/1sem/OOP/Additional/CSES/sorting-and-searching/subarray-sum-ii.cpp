#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, target;
    cin >> n >> target;

    vector<long long> nums(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    vector<long long> prefixSums(n + 1);
    prefixSums[0] = 0ll;

    for (int i = 0; i < n; ++i)
    {
        prefixSums[i + 1] = nums[i] + prefixSums[i];
    }

    long long counter = 0;

    map<long long, long long> m;
    m[0] = 1;

    for (int i = 1; i < n + 1; ++i)
    {
        if (m.find(prefixSums[i] - target) != m.end())
        {
            counter += m[prefixSums[i] - target];
        }
        m[prefixSums[i]]++;
    }

    cout << counter << endl;
}