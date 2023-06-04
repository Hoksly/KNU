#include <bits/stdc++.h>

using namespace std;

pair<int, int> diameterDFS(const vector<vector<int>> &tree, int index, vector<bool> &visited, int &maxDiameter)
{
    visited[index] = true;

    int firstMax = 0, secondMax = 0;

    for (auto child : tree[index])
    {
        if (visited[child])
            continue;
        const auto [childFirst, childSecond] = diameterDFS(tree, child, visited, maxDiameter);

        ignore = childSecond;

        if (childFirst > firstMax)
        {
            secondMax = firstMax;
            firstMax = childFirst;
        }

        else if (childFirst > secondMax)
        {
            secondMax = childFirst;
        }
    }
    maxDiameter = max(maxDiameter, firstMax + 1 + secondMax);

    return {firstMax + 1, secondMax + 1};
}

int main()
{
    int n, a, b;

    int c = int();

    int maxDiameter = 0;

    cout << maxDiameter - 1 << '\n';
}