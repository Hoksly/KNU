#include <bits/stdc++.h>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;

    vector<vector<int>> mp(m, vector<int>(n, 0));

    char c;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> c;
            if (c == '.')
            {
                mp[i][j] = 1;
            }
        }
    }

    int counter = 0;

    queue<pair<int, int>> q;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (mp[i][j])
            {
                for (auto v : mp)
                {
                    for (int i : v)
                    {
                        cout << ((i ? '.' : '#'));
                    }
                    cout << endl;
                }
                cout << endl;
                q.push({i, j});
                mp[i][j] = 0;
                counter++;
                while (!q.empty())
                {
                    int i_cur, j_cur;
                    i_cur = q.back().first;
                    j_cur = q.back().second;
                    q.pop();

                    if (j_cur < n - 1 && mp[i_cur][j_cur + 1])
                    {
                        mp[i_cur][j_cur + 1] = 0;
                        q.push({i_cur, j_cur + 1});
                        cout << "Added " << q.back().first << ' ' << q.back().second << endl;
                    }

                    if (j_cur > 0 && mp[i_cur][j_cur - 1])
                    {
                        mp[i_cur][j_cur - 1] = 0;
                        q.push({i_cur, j_cur - 1});
                        cout << "Added " << q.back().first << ' ' << q.back().second << endl;
                    }

                    if (i_cur < m - 1 && mp[i_cur + 1][j_cur])
                    {
                        mp[i_cur + 1][j_cur] = 0;
                        q.push({i_cur + 1, j_cur});
                        cout << "Added " << q.back().first << ' ' << q.back().second << endl;
                    }

                    if (i_cur > 0 && mp[i_cur - 1][j_cur])
                    {
                        mp[i_cur - 1][j_cur] = 0;
                        q.push({i_cur - 1, j_cur});
                        cout << "Added " << q.back().first << ' ' << q.back().second << endl;
                    }
                }
            }
        }
    }

    cout << counter << endl;
}