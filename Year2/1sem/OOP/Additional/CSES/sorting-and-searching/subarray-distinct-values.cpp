#include <bits/stdc++.h>
using namespace std;

long long nums[200001];

int main()
{
    map<long long, int> curMap;

    long long total = 0ll;

    size_t n, k;
    cin >> n >> k;

    for (size_t i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    size_t leftPtr, rightPtr;
    leftPtr = rightPtr = 0;

    while (rightPtr != n)
    {

        if (curMap.find(nums[rightPtr]) != curMap.end())
        {

            curMap[nums[rightPtr]]++;
            rightPtr++;
            total += rightPtr - leftPtr;
        }
        else
        {
            if (curMap.size() < k)
            {
                curMap[nums[rightPtr]]++;
                rightPtr++;
                total += rightPtr - leftPtr;
            }
            else
            {

                while (curMap.size() >= k)
                {

                    curMap[nums[leftPtr]]--;
                    if (curMap[nums[leftPtr]] == 0)
                    {

                        curMap.erase((nums[leftPtr]));
                    }

                    leftPtr++;
                }
            }
        }
    }

    cout << total << endl;
}