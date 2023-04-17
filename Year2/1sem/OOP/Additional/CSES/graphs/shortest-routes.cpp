#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m, a, b, c;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);

    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b >> c;

        graph[a - 1].push_back({b - 1, c});
    }

    vector<int> distance(n, INT_MIN);
    vector<int> visited(n, 0);

    distance[0] = 0;

    queue<pair<int, int>> q;

    q.push({0, 0});

    while (!q.empty())
    {
        int a = q.front().second;
        q.pop();

        if (visited[a])
            continue;
        visited[a] = 1;
        for (auto pp : graph[a])
        {
            int node = pp.first, weight = pp.second;
            if (distance[a] + weight < distance[b])
            {
                distance[b] = distance[a] + weight;
                q.push({-distance[b], b});
            }
        }
    }

    for (int i : distance)
        cout << i << ' ';
    cout << endl;
}