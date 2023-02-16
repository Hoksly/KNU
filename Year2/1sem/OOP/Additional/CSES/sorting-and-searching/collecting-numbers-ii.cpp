#include <bits/stdc++.h>

using namespace std;

inline int addLeftAndRightInv(vector<int> &arr, int l, int r, int n)
{
    int res = 0;
    res += (l > 0 && arr[l - 1] > arr[l]) ? 1 : 0;
    res += (arr[l] > arr[l + 1]) ? 1 : 0;

    return res;
}

inline int addRightInv(vector<int> *arr, int l, int r, int n)
{
    int res = 0;
    res += (r < n - 1 && arr[r] > arr[r + 1]) ? 1 : 0;
    res += (arr[r - 1] > arr[r]) ? 1 : 0;

    res += (r < n - 1 && arr[r] > arr[r + 1]) ? 1 : 0;
    if (r > l + 1)
    {
        res += (arr[r - 1] > arr[r]) ? 1 : 0;
    }

    return res;
}

inline int diff(vector<int> &arr, int l, int r, int n)
{
    if (l > r)
        return diff(arr, r, l, n);

    int res = 0, tmp;

    res += (l > 0 && arr[l - 1] > arr[l]) ? 1 : 0;
    res += (arr[l] > arr[l + 1]) ? 1 : 0;

    res += (r < n - 1 && arr[r] > arr[r + 1]) ? 1 : 0;
    if (r > l + 1)
    {
        res += (arr[r - 1] > arr[r]) ? 1 : 0;
    }
    res = -res;

    swap(arr[l], arr[r]);

    res += (l > 0 && arr[l - 1] > arr[l]) ? 1 : 0;
    res += (arr[l] > arr[l + 1]) ? 1 : 0;

    res += (r < n - 1 && arr[r] > arr[r + 1]) ? 1 : 0;
    if (r > l + 1)
    {
        res += (arr[r - 1] > arr[r]) ? 1 : 0;
    }

    return res;
}

int main()
{
    // freopen("inp.txt", "r", stdin);

    int n, m, num;
    cin >> n >> m;

    vector<int> index_arr(n);
    vector<int> arr(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> num;
        arr[i] = num;

        index_arr[num - 1] = i;
    }

    int ans = 1;

    for (int i = 1; i < n; ++i)
    {
        if (index_arr[i - 1] > index_arr[i])
            ++ans;
    }
    int l, r;
    for (int i = 0; i < m; ++i)
    {
        cin >> l >> r;
        if (l == r)
        {
            cout << ans << '\n';
            continue;
        }

        ans += diff(index_arr, arr[l - 1] - 1, arr[r - 1] - 1, n);
        swap(arr[l - 1], arr[r - 1]);
        cout << ans << '\n';
    }
}