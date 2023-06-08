#include <bits/stdc++.h>

using namespace std;

int arr[26];

int main()
{
    cin.tie(NULL)->sync_with_stdio();

    int t, n, k;
    string s;

    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        cin >> s;
        fill(arr, arr + 26, 0);
        for (char c : s)
        {
            arr[c - 'a']++;
        }

        int mx = -1;
        for (int i = 0; i < 26; ++i)
        {
            if (arr[i] > 0)
            {
                mx = max(mx, 1 + (arr[i] - 1) / k);
            }
        }
        cout << mx << '\n';
    }
}
