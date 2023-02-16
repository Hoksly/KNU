#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    vector<long long> nums(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    vector<long long> prefixSums(n + 1);
    prefixSums[0] = 0ll;

    unordered_map<long long, long long> m;
    for (int i = 0; i < n; ++i)
    {
        prefixSums[i + 1] = ((nums[i] + prefixSums[i]) % n + n) % n;
        m[prefixSums[i + 1]]++;
    }
    long long counter = 0;

    for (auto iter : m)
    {

        if (iter.first == 0ll)
        {
            counter += ((iter.second) * (iter.second + 1) / 2ll);
        }
        else
        {
            counter += ((iter.second) * (iter.second - 1) / 2ll);
        }
    }

    cout << counter << endl;
}