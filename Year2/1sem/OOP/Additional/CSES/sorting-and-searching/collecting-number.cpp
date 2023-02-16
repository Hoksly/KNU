#include <bits/stdc++.h>

using namespace std;
int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];
    int *index_arr = new int[n];

    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        index_arr[arr[i] - 1] = i;
    }
    int ans = 1;
    for (int i = 1; i < n; ++i)
    {
        if (index_arr[i - 1] > index_arr[i])
            ++ans;
    }
    cout << ans << endl;
}