#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int res = 0;

    for (int i = 5; n / i > 0; i *= 5)
    {
        res += (n / i);
    }
    cout << res << endl;
}