#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    vector<pair<long long, long long>> tasks(n);

    for (long long i = 0; i < n; ++i)
    {
        cin >> tasks[i].first >> tasks[i].second;
    }

    sort(tasks.begin(), tasks.end());

    long long curTime = 0, totalScore = 0;
    for (long long i = 0; i < n; ++i)
    {
        curTime += tasks[i].first;
        totalScore += tasks[i].second - curTime;
    }

    cout << totalScore;
}