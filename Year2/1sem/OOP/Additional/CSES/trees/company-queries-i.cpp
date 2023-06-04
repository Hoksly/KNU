#include <bits/stdc++.h>

using namespace std;

void dfs(const vector<vector<int>> &tree, int node, int parent, vector<int> &parents)
{
    parents[node] = parent;

    for (auto child : tree[node])
    {
        if (child == parent)
            continue;
        dfs(tree, child, node, parents);
    }
}

vector<vector<int>> preProcessTree(const vector<vector<int>> &tree)
{
    int n = 0;
    for (int i = 1; i < tree.size(); i *= 2)
        n++;

    vector<vector<int>> preprocessedTree(n, vector<int>(tree.size(), -1));
    dfs(tree, 0, -1, preprocessedTree[0]);

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < tree.size(); j++)
        {
            if (preprocessedTree[i - 1][j] == -1)
                continue;
            if (preprocessedTree[i - 1][j] != -1)
                preprocessedTree[i][j] = preprocessedTree[i - 1][preprocessedTree[i - 1][j]];
            else
                preprocessedTree[i][j] = -1;
        }
    }
    return preprocessedTree;
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

    vector<vector<int>> preprocessedTree = preProcessTree(tree);

    for (int i = 0; i < q; i++)
    {
        int x, k;
        cin >> x >> k;
        x--;

        int level = 0;

        while (k > 0)
        {
            if (x == -1)
                break;
            if (level >= preprocessedTree.size() || x >= preprocessedTree[level].size())
            {
                x = -1;
                break;
            }

            if (k % 2 == 1)
                x = preprocessedTree[level][x];
            k /= 2;
            level++;
        }

        x = x == -1 ? x : x + 1;
        cout << x << '\n';
    }
}