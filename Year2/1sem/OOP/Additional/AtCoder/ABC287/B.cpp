#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    string s;
    string slice;

    unordered_multiset<string> S;
    unordered_set<string> T;

    for (int i = 0; i < n; ++i)
    {
        cin >> s;
        slice = s.substr(3, 5);

        S.insert(slice);
    }

    for (int i = 0; i < m; ++i)
    {
        cin >> s;
        T.insert(s);
    }

    int ans = 0;
    for (auto ptr = S.begin(); ptr != S.end(); ptr++)
    {
        if (T.find(*ptr) != T.end())
        {

            ans++;
        }
    }
    cout << ans << '\n';
}