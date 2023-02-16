#include <bits/stdc++.h>
using namespace std;

struct triple
{
    int first;
    int second;
    int third;

    triple() = default;
};

struct action
{

    int time;
    bool isAriving = false;
    int visitor;
    action() = default;

    bool operator<(const action &b)
    {
        return this->time < b.time;
    }
};

int main()
{
    freopen("inp.txt", "r", stdin);
    int n;
    vector<action> times(n * 2);
    cin >> n;
    map<int, int> roomsOcupated;

    for (int i = 0; i < n; ++i)
    {
        cin >> times[2 * i].time >> times[2 * i + 1].time;
        times[2 * i].visitor = times[2 * i].visitor = i;
        times[2 * i].isAriving = true;
        times[2 * i + 1].isAriving = false;
    }

    sort(times.begin(), times.end());
    vector<int> ans(n);

    int totalRooms = 0;
    for (int i = 0; i < 2 * n; ++i)
    {
        if (roomsOcupated.size() == 1)
        {
                }
    }
}