#include <bits/stdc++.h>

using namespace std;

struct triple
{
    int frst;
    int sec;
    int thrd;
};
inline bool cmp(const triple &a, const triple &b)
{
    if (a.frst == b.frst)
    {
        if (a.sec == b.sec)
        {
            return a.thrd < b.thrd;
        }
        else
        {
            a.sec < b.sec;
        }
    }
    else
    {
        return a.frst < b.frst;
    }
}

int main()
{
    int n;
    cin >> n;
    vector<triple> projects(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> projects[i].frst >> projects[i].sec >> projects[i].thrd;
    }
    cout << endl;

    sort(projects.begin(), projects.end(), cmp);

    for (auto a : projects)
    {
        cout << a.frst << ' ' << a.sec << ' ' << a.thrd << endl;
    }
}