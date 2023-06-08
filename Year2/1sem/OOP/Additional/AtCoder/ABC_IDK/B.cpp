#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio();

    int n, counter;
    string s;
    cin >> n;
    cin >> s;

    for (int l = 1; l < n; ++l)
    {
        counter = 0;
        for (int i = 0; i < n - l; ++i)
        {
            if (s[i] != s[i + l])
                ++counter;
            else
                break;
        }
        cout << counter << '\n';
    }
}