#include <bits/stdc++.h>

using namespace std;

struct action
{
    int time;
    bool arrive;
    action(int t, bool a) : time(t), arrive(a) {}
    action() = default;

    bool operator<(const action &a)
    {
        return this->time < a.time;
    }
};

int main()
{
    int n, arr, left;
    cin >> n;

    vector<action> actions(2 * n);

    for (int i = 0; i < n; ++i)
    {
        cin >> arr >> left;
        actions[2 * i] = action(arr, true);
        actions[2 * i + 1] = action(left, false);
    }
    sort(actions.begin(), actions.end());

    int cur = 0, maxCustomers = -1;
    for (action act : actions)
    {
        if (act.arrive)
        {
            ++cur;
            maxCustomers = max(cur, maxCustomers);
        }
        else
            --cur;
    }
    cout << maxCustomers << endl;
}