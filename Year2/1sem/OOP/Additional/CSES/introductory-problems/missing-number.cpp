#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio();

    int n, cur;
    cin >> n;
    bool *isPresent = new bool[n];
    fill(isPresent, isPresent + n, false);

    for (int i = 0; i < n - 1; ++i)
    {
        cin >> cur;
        isPresent[cur - 1] = true;
    }
    for (int i = 0; i < n; ++i)
    {
        if (!isPresent[i])
            cout << i + 1 << '\n';
    }
}