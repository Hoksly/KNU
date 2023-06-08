#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    string s;
    int agr = 0;

    for (int i = 0; i < n; ++i)
    {
        cin >> s;
        if (s == "For")
            agr++;
        else
            agr--;
    }
    cout << ((agr > 0) ? "Yes" : "No") << '\n';
}