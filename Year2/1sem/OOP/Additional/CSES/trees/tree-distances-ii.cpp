#include <bits/stdc++.h>

using namespace std;
/*
struct DfsVisitor
{
    virtual inline void beforeEdge(int node, int parent) {}
    virtual inline void afterEdge(int node, int parent) {}
    virtual inline void beforeNode(int node) {}
    virtual inline void afterNode(int node) {}
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
*/
void dfs1(const vector<vector<int>> &tree, int node, int parent, vector<long long> &dp, vector<long long> &ans, int depth = 0)
{
    ans[0] += depth;
    dp[node] = 1;
    for (auto child : tree[node])
    {
        if (child == parent)
            continue;

        dfs1(tree, child, node, dp, ans, depth + 1);
        dp[node] += dp[child];
    }
}

void dfs2(const vector<vector<int>> &tree, int node, int parent, const vector<long long> &dp, vector<long long> &ans)
{
    for (auto child : tree[node])
    {
        if (child == parent)
            continue;

        ans[child] = ans[node] + tree.size() - 2 * dp[child];
        dfs2(tree, child, node, dp, ans);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b;

    cin >> n;

    vector<vector<int>> tree(n);

    for (int i = 0; i < n - 1; ++i)
    {
        cin >> a >> b;
        --a;
        --b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    vector<long long> dp(n, 0);
    vector<long long> ans(n, 0);

    dfs1(tree, 0, -1, dp, ans);
    dfs2(tree, 0, -1, dp, ans);

    for (auto x : ans)
        cout << x << " ";
}