#include <bits/stdc++.h>

using namespace std;

void dfsCalcSubtreeSize(vector<vector<int>> &treeGraph, vector<int> &subtreeSize, int node, int parent)
{
    subtreeSize[node] = 1;
    for (auto child : treeGraph[node])
    {
        if (child != parent)
        {
            dfsCalcSubtreeSize(treeGraph, subtreeSize, child, node);
            subtreeSize[node] += subtreeSize[child];
        }
    }
}

int findCentroid(const vector<vector<int>> &treeGraph, const vector<int> &subtreeSize, int node, int parent, int n)
{
    for (int child : treeGraph[node])
    {
        if (child != parent && subtreeSize[child] > n / 2)
        {
            return findCentroid(treeGraph, subtreeSize, child, node, n);
        }
    }
    return node;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, x, y;
    cin >> n;
    vector<vector<int>> treeGraph(n + 1);
    for (int i = 1; i < n; i++)
    {

        cin >> x >> y;
        treeGraph[x].push_back(y);
        treeGraph[y].push_back(x);
    }
    vector<int> subtreeSize(n, 0);

    dfsCalcSubtreeSize(treeGraph, subtreeSize, 1, 0);
    int xx = findCentroid(treeGraph, subtreeSize, 1, 0, n);

    std::cout << xx << std::endl;
    return 0;
}