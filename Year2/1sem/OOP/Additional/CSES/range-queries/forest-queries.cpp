#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    char tree;

    vector<vector<int>> forest(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> tree;
            forest[i][j] = forest[i - 1][j] + forest[i][j - 1] - forest[i - 1][j - 1];

            if (tree == '*')
                forest[i][j]++;
        }
    }

    int x1, y1, x2, y2;
    for (int i = 0; i < m; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;

        cout << forest[x2][y2] - forest[x1 - 1][y2] - forest[x2][y1 - 1] + forest[x1 - 1][y1 - 1] << '\n';
    }

    return 0;
}