#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

long long nums[200001];

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

int main()
{

    size_t n, k;
    cin >> n >> k;

    indexed_set sortedArray;

    for (size_t i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    for (int i = 0; i < k; ++i)
    {
        sortedArray.insert({nums[i], i});
    }

    if (k & 1)
    {

        cout << (sortedArray.find_by_order(k / 2)->first) << ' ';
        for (int i = k; i < n; ++i)
        {

            sortedArray.erase(sortedArray.find({nums[i - k], i - k}));
            sortedArray.insert({nums[i], i});
            cout << (sortedArray.find_by_order(k / 2)->first) << ' ';
        }
    }
    else
    {
        cout << min(sortedArray.find_by_order(k / 2)->first, sortedArray.find_by_order(k / 2 - 1)->first) << ' ';
        for (int i = k; i < n; ++i)
        {
            sortedArray.erase(sortedArray.find({nums[i - k], i - k}));
            sortedArray.insert({nums[i], i});

            cout << min(sortedArray.find_by_order(k / 2)->first, sortedArray.find_by_order(k / 2 - 1)->first) << ' ';
        }
    }
    cout << endl;
}