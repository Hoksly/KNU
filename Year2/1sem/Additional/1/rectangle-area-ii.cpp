#include <bits/stdc++.h>
using namespace std;

struct triple
{
    int x;
    int beg;
    int end;
    triple(int a, int b, int c) : x(a), beg(b), end(c) {}
};

void split(vector<vector<int>> &V, vector<triple> &ret)
{
}

long solve(vector<vector<int>> &V)
{
    long long res = 0;
}

// An Interval
struct Interval
{
    int s, e;
};

// Function used in sort
bool mycomp(Interval a, Interval b) { return a.s < b.s; }
inline bool comp(triple a, triple b) { return a.beg < b.beg; }

void mergeone(vector<triple> &V)
{
    sort(V.begin(), V.end(), comp);

    int indx = 0, n = V.size();

    for (int i = 1; i < n; ++i)
    {
    }
}

void mergeIntervals(Interval arr[], int n)
{
    // Sort Intervals in increasing order of
    // start time
    sort(arr, arr + n, mycomp);

    int index = 0; // Stores index of last element
    // in output array (modified arr[])

    // Traverse all input Intervals
    for (int i = 1; i < n; i++)
    {
        if (arr[index].e >= arr[i].s)
        {
            // Merge previous and current Intervals
            arr[index].e = max(arr[index].e, arr[i].e);
        }
        else
        {
            index++;
            arr[index] = arr[i];
        }
    }

    // Now arr[0..index-1] stores the merged Intervals
    cout << "\n The Merged Intervals are: ";
    for (int i = 0; i <= index; i++)
        cout << "[" << arr[i].s << ", " << arr[i].e << "] ";
}

// Driver program
int main()
{
    Interval arr[] = {{6, 8}, {1, 9}, {2, 4}, {4, 7}};
    int n = sizeof(arr) / sizeof(arr[0]);
    mergeIntervals(arr, n);
    return 0;
}
