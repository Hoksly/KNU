#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, iCopy;
    cin >> n;

    vector<int> arr(n + 1, INT_MAX);
    arr[0] = 0;

    for (int i = 1; i < n + 1; ++i)
    {

        iCopy = i;
        while (iCopy > 0)
        {
            arr[i] = min(arr[i], arr[i - iCopy % 10]);
            iCopy /= 10;
        }
        arr[i]++;
    }

    cout << arr[n] << endl;
}