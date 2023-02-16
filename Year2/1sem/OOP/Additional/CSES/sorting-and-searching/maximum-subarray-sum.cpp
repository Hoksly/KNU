#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n, curSum, curNum, maxSum = -1000000001;
    curSum = maxSum;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        cin >> curNum;

        curSum = max(curSum + curNum, curNum);
        maxSum = max(maxSum, curSum);
    }
    cout << maxSum << endl;
}

/*
8
-1 3 -2 5 3 -5 2 2
*/