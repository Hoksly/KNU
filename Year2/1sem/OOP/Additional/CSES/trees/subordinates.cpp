#include <bits/stdc++.h>

using namespace std;

struct Node
{
    Node *parent = nullptr;
    size_t index;
    vector<Node *> children;
};

size_t dfs(const vector<vector<size_t>> &tree, size_t index, vector<int> &subordinates)
{
    if (tree[index].empty())
    {
        subordinates[index] = 0;
        return 1;
    }

    size_t count = 0;
    for (auto child : tree[index])
    {
        count += dfs(tree, child, subordinates);
    }
    subordinates[index] = count;

    return count + 1;
}

int main()
{
    int n;
    cin >> n;
    vector<int> company(n - 1);

    for (size_t i = 0; i < n - 1; ++i)
    {
        cin >> company[i];
    }

    vector<vector<size_t>> tree(n);

    for (size_t i = 1; i < n; ++i)
    {
        tree[company[i - 1] - 1].push_back(i);
    }

    vector<int> subordinates(n);
    dfs(tree, 0, subordinates);

    for (auto s : subordinates)
    {
        cout << s << " ";
    }
    return 0;
}
