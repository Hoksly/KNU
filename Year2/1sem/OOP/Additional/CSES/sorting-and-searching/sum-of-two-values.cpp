#include <bits/stdc++.h>

using namespace std;

int main()
{
    unordered_map<int, int> map;

    int n, sum, cur;
    cin >> n >> sum;

    for (int i = 0; i < n; ++i)
    {
        cin >> cur;
        if (map.find(sum - cur) != map.end())
        {
            cout << (map.find(sum - cur)->second + 1) << ' ' << i + 1 << endl;
            return 0;
        }
        map.insert({cur, i});
    }
    cout << "IMPOSSIBLE" << endl;
}