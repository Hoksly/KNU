#include <bits/stdc++.h>

using namespace std;

struct movie
{
    int beg, end;
    movie() = default;
    movie(int b, int e) : beg(b), end(e) {}
};
bool compare(const movie &a, const movie &b)
{
    return a.end < b.end;
}

int main()
{
    int n, beg, end, total = 0;
    cin >> n;
    vector<movie> movies(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> beg >> end;

        movies[i] = movie(beg, end);
    }

    sort(movies.begin(), movies.end(), compare);

    end = movies[0].end;
    total = 1;
    for (int i = 1; i < n; ++i)
    {
        if (end <= movies[i].beg)
        {
            end = movies[i].end;
            ++total;
        }
    }
    cout << total << endl;
    return 0;
}