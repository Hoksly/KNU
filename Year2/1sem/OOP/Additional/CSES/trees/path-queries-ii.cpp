#include <bits/stdc++.h>

using namespace std;

struct DfsVisitor
{
    virtual void beforeEdge(int node, int parent) {}
    virtual void afterEdge(int node, int parent) {}
    virtual void beforeNode(int node) {}
    virtual void afterNode(int node) {}
};

struct CalcDepth : public DfsVisitor
{
    vector<int> depth;
    explicit CalcDepth(int n) : depth(n, 0) {}

    void afterEdge(int node, int parent) override
    {
        depth[node] = max(depth[node], depth[parent] + 1);
    }
};

void _dfs(const vector<vector<int>> &tree, int node, DfsVisitor *visitor, vector<bool> &used)
{
    used[node] = true;

    visitor->beforeNode(node);

    for (auto child : tree[node])
    {
        if (used[child])
            continue;

        visitor->beforeEdge(child, node);
        _dfs(tree, child, visitor, used);
        visitor->afterEdge(child, node);
    }

    visitor->afterNode(node);
}

void dfs(const vector<vector<int>> &tree, int node, DfsVisitor *visitor)
{
    vector<bool> used(tree.size(), false);
    _dfs(tree, node, visitor, used);
}

int main()
{

    int n, a, b, q;

    cin >> n >> q;
    vector<int> values(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> values[i];
    }

    vector<vector<int>> tree(n);
    for (int i = 1; i < n; ++i)
    {
        cin >> a >> b;
        a--, b--;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    int queryType;
    for (int i = 0; i < q; ++i)
    {
        cin >> queryType;
        if (queryType == 1)
        {
            int node, newValue;
            cin >> node >> newValue;
        }
        else // queryType == 2
        {
            int nodeA, nodeB;
            cin >> nodeA >> nodeB;
        }
    }

    CalcDepth calcDepth(n);
    dfs(tree, 0, &calcDepth);
    vector<int> depth = calcDepth.depth;

    return 0;
}