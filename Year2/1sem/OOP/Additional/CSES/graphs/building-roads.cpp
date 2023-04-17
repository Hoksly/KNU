#include <bits/stdc++.h>

using namespace std;

vector<int> bfs(int a, const vector<vector<int>> &graph, vector<int> &visited, int num)
{
    queue<int> q;
    int curNode;
    q.push(a);
    vector<int> ret;
    ret.push_back(a);

    while (!q.empty())
    {
        curNode = q.front();
        q.pop();

        for (int node : graph[curNode])
        {
            if (!visited[node])
            {
                visited[node] = num;
                q.push(node);
                ret.push_back(node);
            }
        }
    }
    return ret;
}

int main()
{
    int n, m, a, b;
    cin >> n >> m;

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;

        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
    int cur = 1;
    vector<int> visited(n, 0);
    vector<vector<int>> components;

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            components.push_back(bfs(i, graph, visited, cur));
            cur++;
        }
    }
    cout << components.size() - 1 << '\n';
    for (int i = 1; i < components.size(); ++i)
    {
        cout << components[i][0] + 1 << ' ' << components[i - 1][0] + 1 << '\n';
    }
}