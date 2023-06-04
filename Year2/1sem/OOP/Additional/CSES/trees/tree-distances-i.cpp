#include <bits/stdc++.h>

using namespace std;

void dfs(const vector<vector<int>> &tree, int node, int parent, vector<int> &firstMax, vector<int> &secondMax, vector<int> &maxLengthChild)
{
    firstMax[node] = 0;
    secondMax[node] = 0;

    for (auto child : tree[node])
    {
        if (child == parent)
            continue;

        dfs(tree, child, node, firstMax, secondMax, maxLengthChild);

        if (firstMax[child] + 1 > firstMax[node])
        {
            secondMax[node] = firstMax[node];
            firstMax[node] = firstMax[child] + 1;
            maxLengthChild[node] = child;
        }

        else if (firstMax[child] + 1 > secondMax[node])
        {
            secondMax[node] = firstMax[child] + 1;
        }
    }
}

// calculate for every node child the
// maximum length of a path through its parent parent
void dfs2(const vector<vector<int>> &tree, int node, int parent, vector<int> &firstMax, vector<int> &secondMax, vector<int> &maxLengthChild)
{
    for (auto child : tree[node])
    {
        if (child == parent)
            continue;

        if (maxLengthChild[node] == child)
        {
            if (firstMax[child] < secondMax[node] + 1)
            {
                secondMax[child] = firstMax[child];
                firstMax[child] = secondMax[node] + 1;
                maxLengthChild[child] = node;
            }
            else
            {
                secondMax[child] = max(secondMax[child], secondMax[node] + 1);
            }
        }
        else
        {
            secondMax[child] = firstMax[child];

            firstMax[child] = firstMax[node] + 1;

            maxLengthChild[child] = node;
        }

        dfs2(tree, child, node, firstMax, secondMax, maxLengthChild);
    }
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, a, b;

    cin >> n;

    vector<vector<int>> tree(n);
    for (int i = 1; i < n; ++i)
    {
        cin >> a >> b;
        a--, b--;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    vector<int> firstMax(n, 0);
    vector<int> secondMax(n, 0);

    vector<int> maxLengthChild(n, 0);

    dfs(tree, 0, -1, firstMax, secondMax, maxLengthChild);
    dfs2(tree, 0, -1, firstMax, secondMax, maxLengthChild);

    for (int i = 0; i < n; ++i)
    {
        cout << firstMax[i] << " ";
    }

    return 0;
}