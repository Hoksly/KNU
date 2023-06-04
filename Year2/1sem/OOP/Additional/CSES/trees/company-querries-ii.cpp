#include <bits/stdc++.h>

using namespace std;

void dfs(const vector<vector<int>> &tree, int node, int parent, vector<int> &traversal, vector<int> &firstAppearance)
{
    traversal.push_back(node);
    if (firstAppearance[node] == -1)
        firstAppearance[node] = traversal.size() - 1;

    for (auto child : tree[node])
    {
        if (child == parent)
            continue;
        dfs(tree, child, node, traversal, firstAppearance);
        traversal.push_back(node);
    }
}

int main()
{
    int n, q;
    cin >> n >> q;

    vector<vector<int>> tree(n);
    for (int i = 1; i < n; i++)
    {
        int a;
        cin >> a;
        tree[i].push_back(a - 1);
        tree[a - 1].push_back(i);
    }

    vector<int> traversal;
    traversal.reserve(2 * n - 1);
    vector<int> firstAppearance(n, -1);
    dfs(tree, 0, -1, traversal, firstAppearance);

    vector<vector<int>> sparseTable(ceil(log2(traversal.size())) + 1, vector<int>(traversal.size(), -1));
    for (int i = 0; i < traversal.size(); i++)
        sparseTable[0][i] = traversal[i];

    for (int i = 1; i < sparseTable.size(); i++)
    {
        for (int j = 0; j < traversal.size(); j++)
        {
            if (j + (1 << (i - 1)) >= traversal.size())
                continue;
            sparseTable[i][j] = min(sparseTable[i - 1][j], sparseTable[i - 1][j + (1 << (i - 1))]);
        }
    }

    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        a = firstAppearance[a];
        b = firstAppearance[b];

        int l = min(a, b);
        int r = max(a, b);

        int k = log2(r - l + 1);
        int ans = min(sparseTable[k][l], sparseTable[k][r - (1 << k) + 1]);
        cout << ans + 1 << endl;
    }
}