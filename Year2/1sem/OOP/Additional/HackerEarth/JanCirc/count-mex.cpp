#include <bits/stdc++.h>

using namespace std;

int main()
{
    // cin.tie(NULL)->sync_with_stdio();
    freopen("input.txt", "r", stdin);
    int_fast32_t *ans = new int_fast32_t[1000000];
    int_fast32_t *map = new int_fast32_t[1000000];

    int_fast32_t t, n, el;
    cin >> t;
    // cout << "All: " << t << endl;

    // vector<int_fast32_t> ans;
    // vector<int_fast32_t> map;

    while (t--)
    {
        cin >> n;

        fill(ans, ans + n, 0);

        for (int i = 0; i < n; ++i)
        {
            cin >> el;
            map[el] = i;
        }

        pair<int_fast32_t, int_fast32_t> interval = {map[0], map[0]};

        for (int i = 1; i < n; ++i)
        {
            if (interval.first < map[i] && map[i] < interval.second)
            {
                continue;
            }

            if (map[i] < interval.first)
            {
                ans[i - 1] = (interval.first - map[i]) * (n - interval.second);
                interval.first = map[i];
            }
            else
            {
                ans[i - 1] = (map[i] - interval.second) * (interval.first + 1);
                interval.second = map[i];
            }
        }
        ans[n - 1] = 1;

        for (int_fast32_t i = 0; i < n; ++i)
            cout << ans[i] << ' ';
        cout << '\n';
    }
}