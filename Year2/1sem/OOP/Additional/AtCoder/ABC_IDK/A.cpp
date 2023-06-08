#include <iostream>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;

    if (b == a * 2 || b == a * 2 + 1)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}