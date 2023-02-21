#include <bits/stdc++.h>

using namespace std;
const int mod = 1000000007;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> countMap(n, vector<int>(n, 0));
    bool **trapMap = new bool *[n];
    char c;
    for (int i = 0; i < n; ++i)
    {
        trapMap[i] = new bool[n];
        for (int j = 0; j < n; ++j)
        {
            cin >> c;
            trapMap[i][j] = (c == '.');
        }
    }
    countMap[0][0] = (int)trapMap[0][0];
    for (int i = 1; i < n; ++i)
    {
        countMap[i][0] = (trapMap[i][0]) ? countMap[i - 1][0] : 0;
        countMap[0][i] = (trapMap[0][i]) ? countMap[0][i - 1] : 0;
    }

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if (trapMap[i][j])
            {
                countMap[i][j] += countMap[i][j - 1] + countMap[i - 1][j];
                countMap[i][j] %= mod;
            }
        }
    }

    cout << countMap[n - 1][n - 1] << endl;
}