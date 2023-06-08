#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> treeGraph(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        treeGraph[x].push_back(y);
        treeGraph[y].push_back(x);
    }
    vector<int> lev(n + 1);
    vector<vector<int>> sparseTable(ceil(log2(n + 1)) + 1, vector<int>(n + 1));
    dfs(1, 0, sparseTable, treeGraph, lev);
    for (int i = 1; i < sparseTable.size(); i++)
    {
        for (int j = 1; j < sparseTable[i].size(); j++)
        {
            sparseTable[i][j] = sparseTable[i - 1][sparseTable[i - 1][j]];
        }
    }
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        cout << lca(x, y, sparseTable, lev) << endl;
    }
    return 0;
}