#include <bits/stdc++.h>

using namespace std;

int main()
{
    int m, n;
    int v1, v2;
    cin >> n >> m;
    if (n == 1 && m == 0)
    {
        cout << "Yes" << endl;
    }

    int *map = new int[n];
    fill(map, map + n, 0);

    for (int i = 0; i < m; ++i)
    {
        cin >> v1 >> v2;
        map[v1 - 1]++;
        map[v2 - 1]++;
        if (map[v1 - 1] > 2 || map[v1 - 1] > 2)
        {
            cout << "No" << endl;
            return 0;
        }
    }

    int oneCount = 0;
    for (int i = 0; i < n; ++i)
    {
        if (map[i] == 1)
            oneCount++;
        if (map[i] == 0 || map[i] > 2)
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << ((oneCount == 2) ? "Yes" : "No") << endl;
}
