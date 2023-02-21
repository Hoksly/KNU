#include <bits/stdc++.h>

using namespace std;

pair<int, int> arr[200001];

int main()
{
    int n, curEl, curPos;

    cin >> n;
    curPos = 0;

    stack<pair<int, int>> q;

    for (int i = 0; i < n; ++i)
    {
        cin >> curEl;
        while (!q.empty() && q.top().second >= curEl)
        {
            q.pop();
        }
        if (q.empty())
        {
            cout << 0 << ' ';
            q.push({i + 1, curEl});
        }
        else
        {
            cout << q.top().first << ' ';

            q.push({i + 1, curEl});
        }
    }
}