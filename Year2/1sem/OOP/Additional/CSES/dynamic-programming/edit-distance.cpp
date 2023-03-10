#include <bits/stdc++.h>

using namespace std;
inline int cost(char a, char b)
{
    return (a == b) ? 0 : 1;
}
int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1, 0));
    for (int i = 0; i < s2.size() + 1; ++i)
    {
        dp[0][i] = i;
    }

    for (int i = 0; i < s1.size() + 1; ++i)
    {
        dp[i][0] = i;
    }
    for (int i = 1; i < s1.size() + 1; ++i)
    {
        for (int j = 1; j < s2.size() + 1; ++j)
        {
            dp[i][j] = min(dp[i - 1][j] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost(s1[i - 1], s2[j - 1])));
        }
    }

    cout << dp[s1.size()][s2.size()] << endl;
}
