#include <bits/stdc++.h>

using namespace std;
int MOD = 1000000007;

inline void generate(int p, int n, vector<int> &ret, int len = 0, int cur = 0)
{
    if (len == n)
    {
        ret.push_back(cur);
        return;
    }

    if (p & (1 << len)) // bit(p, len) = 0
    {
        generate(p, n, ret, len + 1, cur);
    }
    else
    {
        generate(p, n, ret, len + 1, cur + (1 << len));
        if (len < n - 1)
        {

            if ((p & (1 << (len + 1))) == 0)
                generate(p, n, ret, len + 2, cur);
        }
    }
}

int main()
{
    int n, m;

    cin >> n >> m;

    vector<vector<int>> A(m + 1, vector<int>(1 << n, 0));

    vector<vector<int>> D(1 << n);

    for (int i = 0; i < (1 << n); ++i)
    {
        generate(i, n, D[i]);
    }

    A[0][0] = 1;
    for (int i = 1; i < m + 1; ++i)
    {
        for (int j = 0; j < (1 << n); ++j)
        {
            for (int num : D[j])
            {
                A[i][j] += A[i - 1][num];
                A[i][j] %= MOD;
            }
        }
    }
    cout << A[m][0] << endl;
}
/*
1 0 0 0
1 0 0 1
2 0 0 1
3 0 0 2

1 1 2 3
0 0 0 0
0 0 0 0
0 1 1 2

*/