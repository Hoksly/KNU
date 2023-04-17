#include <bits/stdc++.h>

using namespace std;

inline int other(int i)
{
    return (i == 1 ? 2 : 1);
}

int main()
{

    int n, m;
    cin >> n >> m;

    vector<set<int>> graph(n);
    int a, b;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        graph[a - 1].insert(b - 1);
        graph[b - 1].insert(a - 1);
    }

    vector<int> colors(n, 0);
    vector<int> used(n, 0);
    // coloring DFS
    stack<int> q;
    int curNode, curColor;

    for (int i = 0; i < n; ++i)
    {
        if (colors[i] == 0)
        {
            q.push(i);
            colors[i] = 1;
            while (!q.empty())
            {
                curNode = q.top();
                q.pop();
                curColor = colors[curNode];
                for (int node : graph[curNode])
                {
                    if (colors[node] == other(curColor))
                        continue;

                    else if (colors[node] == curColor)
                    {
                        cout << "IMPOSSIBLE" << endl;
                        return 0;
                    }
                    else
                    {
                        colors[node] = other(curColor);
                        q.push(node);
                    }
                }
            }
        }
    }

    for (int color : colors)
    {
        cout << color << ' ';
    }
    cout << endl;
}