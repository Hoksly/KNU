#include <iostream>
using namespace std;

int main()
{
    int T, a, b, x, y;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        cin >> a >> b;

        y = (2 * b - a) / 3;
        x = b - 2 * y;

        // cout << "x, y: " << x << ' ' << y << '\n';
        if (a == 2 * x + y && x >= 0 && y >= 0)
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
    }
}