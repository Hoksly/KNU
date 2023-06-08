#include <iostream>
#include <vector>

using namespace std;

/**
 * Performs depth-first search on the tree graph to calculate sparse table and level information.
 * @param s Current node
 * @param pa Parent node
 * @param sparseTable Sparse table for LCA calculations
 * @param treeGraph Tree graph representation
 * @param lev Level information of nodes
 */
void dfs(int s, int pa, vector<vector<int>> &sparseTable, vector<vector<int>> &treeGraph, vector<int> &lev)
{
    for (auto i : treeGraph[s])
    {
        if (i != pa)
        {
            sparseTable[0][i] = s;
            lev[i] = lev[s] + 1;
            dfs(i, s, sparseTable, treeGraph, lev);
        }
    }
}

/**
 * Raises a node to a given power in the sparse table.
 * @param x Node
 * @param y Power
 * @param sparseTable Sparse table for LCA calculations
 * @return Result of raising the node to the power in the sparse table
 */
int raise(int x, int y, const vector<vector<int>> &sparseTable)
{
    int z = 0;
    while (y > 0)
    {
        if (y & 1)
            x = sparseTable[z][x];
        z++;
        y >>= 1;
    }
    return x;
}

/**
 * Finds the Lowest Common Ancestor (LCA) of two nodes in the tree.
 * @param x First node
 * @param y Second node
 * @param sparseTable Sparse table for LCA calculations
 * @param lev Level information of nodes
 * @return LCA of the two nodes
 */
int lca(int x, int y, const vector<vector<int>> &sparseTable, const vector<int> &lev)
{
    if (lev[x] > lev[y])
        swap(x, y);
    int d = lev[y] - lev[x];
    y = raise(y, d, sparseTable);
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
    {
        if (sparseTable[i][x] != sparseTable[i][y])
        {
            x = sparseTable[i][x];
            y = sparseTable[i][y];
        }
    }
    return sparseTable[0][x];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    // Construct the tree graph
    vector<vector<int>> treeGraph(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        treeGraph[x].push_back(y);
        treeGraph[y].push_back(x);
    }

    // Calculate sparse table and level information
    vector<vector<int>> sparseTable(21, vector<int>(n + 1));
    vector<int> lev(n + 1);
    dfs(1, 0, sparseTable, treeGraph, lev);

    // Populate the sparse table
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            sparseTable[i][j] = sparseTable[i - 1][sparseTable[i - 1][j]];
        }
    }

    // Answer LCA queries
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        int z = lca(x, y, sparseTable, lev);
        cout << (lev[y] + lev[x] - 2 * lev[z]) << "\n";
    }

    return 0;
}
