#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, target;
    cin >> n >> target;

    vector<long long> nums(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    vector<long long> prefixSums(n + 1);
    prefixSums[0] = 0ll;

    for (int i = 0; i < n; ++i)
    {
        prefixSums[i + 1] = nums[i] + prefixSums[i];
    }

    int rightPtr = 1, leftPtr = 0, counter = 0;

    while (rightPtr != n)
    {
        if (prefixSums[rightPtr] - prefixSums[leftPtr] == target)
        {
            rightPtr++;
            counter++;
        }
        else if (prefixSums[rightPtr] - prefixSums[leftPtr] > target)
        {

            leftPtr++;
        }
        else
        {
            rightPtr++;
        }
    }

    while (leftPtr != n)
    {
        if (prefixSums[n] - prefixSums[leftPtr] == target)
            counter++;
        leftPtr++;
    }

    cout << counter << endl;
}