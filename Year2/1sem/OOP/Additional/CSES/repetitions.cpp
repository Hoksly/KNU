#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio();
    int repetitions = 1, maxRepetitions = 0, n;
    char cur;
    string s;

    cin >> s;
    n = s.size();
    cur = s[0];

    for (int i = 1; i < n; ++i)
    {
        if (s[i] == cur)
            ++repetitions;
        else
        {
            maxRepetitions = max(repetitions, maxRepetitions);
            repetitions = 1;
            cur = s[i];
        }
    }
    cout << max(repetitions, maxRepetitions) << '\n';

    
}