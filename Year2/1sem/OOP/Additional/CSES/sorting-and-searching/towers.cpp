#include <bits/stdc++.h>

using namespace std;

int arr[200001];

int multysetSolution(int n)
{
    multiset<int> set;

    int curCube;
    set.insert(arr[0]);

    for (int i = 1; i < n; ++i)
    {
        curCube = arr[i];
        auto uBound = set.upper_bound(curCube);
        if (set.upper_bound(curCube) != set.end())
        {
            set.erase(uBound);
            set.insert(curCube);
        }
        else
        {
            set.insert(curCube);
        }
    }

    return static_cast<int>(set.size());
}

int binarySearchSolution(int n)
{
    vector<int> towers;
    towers.push_back(arr[0]);
    vector<int>::iterator iter;
    int low = 0, mid, end = n;
    for (int i = 1; i < n; ++i)
    {
        low = 0;
        end = towers.size();

        while (end - low > 1)
        {
            mid = (low + end) / 2;
            if (towers[mid] >= arr[i])
            {
                towers
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
}