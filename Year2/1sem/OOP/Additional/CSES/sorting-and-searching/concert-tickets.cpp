#include <bits/stdc++.h>

using namespace std;

int main()
{
    multiset<int> tickets;

    int n, m, ticket, maxPrice;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        cin >> ticket;
        tickets.insert(ticket);
    }

    for (int i = 0; i < m; ++i)
    {
        cin >> maxPrice;
        auto price = tickets.upper_bound(maxPrice);
        if (price == tickets.begin())
        {
            cout << "-1" << '\n';
        }
        else
        {

            cout << *(--price) << '\n';
            tickets.erase(price);
        }
    }
}