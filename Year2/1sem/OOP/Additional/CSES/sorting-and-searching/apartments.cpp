#include <bits/stdc++.h>

using namespace std;

inline int satisfy(const vector<int> &applicants, const vector<int> &apartaments, int k)
{
    int applPointer = 0, appartPointer = 0, total = 0;

    while (applPointer < applicants.size() && appartPointer < apartaments.size())
    {
        if (abs(applicants[applPointer] - apartaments[appartPointer]) <= k)
        {
            total++;
            appartPointer++;
            applPointer++;
        }
        else
        {
            if (applicants[applPointer] > apartaments[appartPointer])
                appartPointer++;
            else
                applPointer++;
        }
    }
    return total;
}

int main()
{
    int n, m, k;

    cin >> n >> m >> k;

    vector<int> people(n);
    vector<int> rooms(m);

    for (int i = 0; i < n; ++i)
    {
        cin >> people[i];
    }

    for (int i = 0; i < m; ++i)
        cin >> rooms[i];

    sort(rooms.begin(), rooms.end());
    sort(people.begin(), people.end());
    cout << satisfy(people, rooms, k) << endl;
}