#include <bits/stdc++.h>

using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    string s, t;
    cin >> s >> t;

    int n = t.size();
    bool *map = new bool[n];
    fill(map, map + n, false);
    bool match = true;
    for (int i = 0; i < n; ++i)
    {
        match = match && (s[s.size() - 1 - i] == t[n - 1 - i] || s[s.size() - 1 - i] == '?' || t[n - 1 - i] == '?');
        map[n - 1 - i] = match;
    }

    cout << ((map[0]) ? "Yes" : "No") << '\n';

    match = true;
    for (int i = 0; i < n - 1; ++i)
    {
        match = match && (s[i] == t[i] || s[i] == '?' || t[i] == '?');
        if (match && map[i + 1])
            cout << "Yes";
        else
            cout << "No";
        cout << '\n';
    }
    cout << ((match) ? "Yes" : "No") << '\n';
}