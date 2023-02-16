#include <bits/stdc++.h>

using namespace std;

int main()
{
    multiset<int> points;
    multiset<int> intervals;
    ios::sync_with_stdio();
    cin.tie(0);
    cout.tie(0);
    // freopen("inp.txt", "r", stdin);
    int x, n;
    cin >> x >> n;

    multiset<int>::iterator low_bound, high_bound;

    multiset<int>::iterator maxElement;

    points.insert(0);
    points.insert(x);
    intervals.insert(x);

    for (int i = 0; i < n; ++i)
    {
        cin >> x;

        low_bound = points.lower_bound(x);
        low_bound--;
        high_bound = points.upper_bound(x);
        points.insert(x);

        intervals.erase(intervals.find(*high_bound - *low_bound));
        intervals.insert(*high_bound - x);
        intervals.insert(x - *low_bound);

        maxElement = intervals.end();
        maxElement--;
        cout << *maxElement << ' ';
    }
}