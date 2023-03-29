#include <bits/stdc++.h>

using namespace std;

int log2_floor(unsigned long long i)
{
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

int st[25][2000001];

int main()
{
    int n, q, L, R;
    cin >> n >> q;
    vector<int> array(n);
    for (int i = 0; i < n; ++i)
        cin >> array[i];

    std::copy(array.begin(), array.end(), st[0]);
    int K = log2_floor(n);

    for (int i = 1; i <= K; i++)
        for (int j = 0; j + (1 << i) <= n; j++)
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);

    for (int i = 0; i < q; ++i)
    {
        cin >> L >> R;
        L--;
        R--;
        int k = log2_floor(R - L + 1);
        cout << min(st[k][L], st[k][R - (1 << k) + 1]) << '\n';
    }
}