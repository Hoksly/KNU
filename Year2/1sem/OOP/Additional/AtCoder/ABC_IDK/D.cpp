#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;

int main()
{
    map<string, vector<string>> Graph;
    map<string, bool> visited;
    int n;
    cin >> n;
    string s, t, curNode;
    for (int i = 0; i < n; ++i)
    {
        cin >> s >> t;

        if (s == t)
            continue;
        Graph[s].push_back(t);
        visited[s] = false;
        visited[t] = false;
    }

    stack<string> toVisit;

    for (auto node = Graph.begin(); node != Graph.end(); node++)
    {
        if (!visited[node->first])
        {
            toVisit.push(node->first);
            visited[node->first] = true;
            while (!toVisit.empty())
            {
                curNode = toVisit.top();
                visited[curNode] = true;
                toVisit.pop();
                for (string connectedNode : Graph[curNode])
                {
                    if (visited[connectedNode])
                    {
                        cout << "No" << endl;
                        return 0;
                    }

                    toVisit.push(connectedNode);
                }
            }
        }
    }
    cout << "Yes" << endl;

    return 0;
}