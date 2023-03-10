#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b, n;
    cin >> a >> b;

    vector<vector<int>> mp(max(a, b) + 1, vector<int>(max(a, b) + 1, INT_MAX));
    n = max(a, b) + 1;
    for (int i = 1; i < n; ++i)
    {
        mp[i][0] = mp[0][i] = i - 1;
        mp[i][i] = 0;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {

            for (int q = 1; q < i; ++q)
            {
                mp[i][j] = min(mp[i][j], 1 + mp[i - q][j] + mp[q][j]);
            }
            for (int q = 1; q < j; ++q)
            {
                mp[i][j] = min(mp[i][j], 1 + mp[i][j - q] + mp[i][q]);
            }
            mp[j][i] = mp[i][j];
        }
    }

    cout << mp[a][b] << endl;
}