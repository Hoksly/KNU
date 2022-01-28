#include <iostream>
#include <algorithm>

using namespace std;

int main ()
{
    long long int sum = 0;
    int n;
    cin >> n;
    string a [n];
    for (int i = 0; i < n; i ++) {cin >> a [i];}
    sort (a, a + n);

    for (int i = 0; i < n; i ++)
    {
        long long int ls = 0;
        for (char j : a [i])
        {
            ls += (j - 64);
        }
        sum += ls * (i + 1);
    }

    cout << sum << endl;
    return 0;
}