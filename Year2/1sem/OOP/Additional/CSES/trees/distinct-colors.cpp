#include <bits/stdc++.h>

using namespace std;

set<int> calculateColors(
    const vector<vector<int>> &treeGraph,
    const vector<int> &colors,
    vector<int> &differentColors,
    int node,
    int parent)
{
    set<int> nodeColors;
    nodeColors.insert(colors[node]);

    for (auto child : treeGraph[node])
    {
        if (child == parent)
            continue;

        const set<int> &childColors = calculateColors(treeGraph, colors, differentColors, child, node);
        nodeColors.insert(childColors.begin(), childColors.end());
    }

    differentColors[node] = nodeColors.size();

    return move(nodeColors);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, x, y;
    cin >> n;
    vector<vector<int>> treeGraph(n + 1);
    vector<int> colors(n + 1, 0);
    n++;
    for (int i = 1; i < n; i++)
    {
        cin >> colors[i];
    }
    n--;

    for (int i = 1; i < n; i++)
    {

        cin >> x >> y;
        treeGraph[x].push_back(y);
        treeGraph[y].push_back(x);
    }

    vector<int> differentColors(n + 1, 0);
    calculateColors(treeGraph, colors, differentColors, 1, 0);
    for (auto x = ++differentColors.begin(); x != differentColors.end(); x++)
    {
        cout << *x << " ";
    }
    cout << '\n';
}