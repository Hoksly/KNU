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

    vector<long long> distance(n, LLONG_MAX);
    vector<int> visited(n, 0);

    distance[0] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;

    q.push({0, 0});

    while (!q.empty())
    {
        int a = q.top().second;
        q.pop();

        if (visited[a])
            continue;

        visited[a] = 1;
        for (auto pp : graph[a])
        {
            int node = pp.first, weight = pp.second;
            if (distance[a] + weight < distance[node])
            {
                distance[node] = distance[a] + weight;
                q.push({distance[node], node});
            }
        }
    }

    for (long long i : distance)
        cout << i << ' ';
    cout << endl;
}
