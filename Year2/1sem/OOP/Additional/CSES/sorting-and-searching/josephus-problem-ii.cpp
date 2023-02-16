#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

int main()
{
    int n, k;
    cin >> n >> k;

    indexed_set circle;

    for (int i = 0; i < n; ++i)
    {
        circle.insert(i + 1);
    }

    int cur = 0;

    for (int i = 0; i < n; ++i)
    {
        cur += k;
        cur %= circle.size();

        auto node = circle.find_by_order(cur);
        cout << *node << ' ';
        circle.erase(node);
    }
}