#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n % 4 == 1 || n % 4 == 2)
    {
        cout << "NO" << '\n';
        return 0;
    }
    cout << "YES" << endl;
    if (n % 4 == 3)
    {
        cout << (n / 2) + 1 << endl;
        cout << "1 2 ";
        for (int i = 0; i < n / 4; ++i)
            cout << (i + 1) * 4 << ' ' << (i + 1) * 4 + 3 << ' ';
        cout << endl;

        cout << n / 2 << endl;
        cout << "3 ";
        for (int i = 0; i < n / 4; ++i)
            cout << (i + 1) * 4 + 1 << ' ' << (i + 1) * 4 + 2 << ' ';
        cout << endl;
    }
    else
    {
        cout << (n / 2) << endl;
        cout << "1 4 ";
        for (int i = 1; i < n / 4; ++i)
            cout << i * 4 + 1 << ' ' << i * 4 + 4 << ' ';
        cout << endl;

        cout << n / 2 << endl;
        cout << "2 3 ";
        for (int i = 1; i < n / 4; ++i)
            cout << i * 4 + 2 << ' ' << i * 4 + 3 << ' ';
        cout << endl;
    }
    return 0;
}
