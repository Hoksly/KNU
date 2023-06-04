#include <bits/stdc++.h>

using namespace std;

pair<int, int> goDfs(const vector<vector<int>> &tree, int node, vector<bool> &used)
{
    if (tree[node].empty())
        return {0, 0};

    used[node] = true;

    int retFirst = 0, restSecond = 0;
    bool addOne = false;
    for (auto child : tree[node])
    {
        if (used[child])
            continue;

        auto [first, second] = goDfs(tree, child, used);
        if (first == second)
            addOne = true;
        restSecond += first;
    }
    retFirst = restSecond;

    return {retFirst + static_cast<int>(addOne), restSecond};
}

int main()
{

    size_t n;
    cin >> n;

    vector<vector<int>> tree(n);

    for (size_t i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;

        tree[a].emplace_back(b);
        tree[b].emplace_back(a);
    }
    vector<bool> used(n, false);
    std::cout << goDfs(tree, 0, used).first << '\n';

    return 0;
}