#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio();

    long begin;
    cin >> begin;

    while (begin != 1)
    {
        cout << begin << ' ';
        if (begin % 2)
        {
            begin *= 3;
            begin += 1;
        }
        else
            begin /= 2;
    }
    cout << 1 << endl;
}