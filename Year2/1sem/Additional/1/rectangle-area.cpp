#include <bits/stdc++.h>
using namespace std;

struct line
{
    int x;
    int s;
    int e;
    line(int a, int b, int c)
    {
        x = a;
        s = b;
        e = c;
    }
};

void split(int x0, int y0, int x1, int y1, vector<line> &V)
{
    for (int i = x0; i < x1; i++)
    {
        V.push_back(line(i, y0, y1));
    }
}

bool mycomp(line &a, line &b)
{
    if (a.x == b.x)
        return a.s < b.s;
    else
        return a.x < b.x;
}

void print_V(vector<line> &V)
{
    for (int i = 0; i < V.size(); ++i)
    {
        cout << V[i].x << ' ' << V[i].s << ' ' << V[i].e << endl;
    }
}

int merge(vector<line> V)
{
    sort(V.begin(), V.end(), mycomp);

    int n = V.size(), index, x, beg;
    index = 0;
    x = V[0].x;
    vector<line> res;

    for (int i = 1; i < n; ++i)
    {
        cout << endl
             << endl;
        print_V(res);
        // so it has same x as previous interval
        while (i < n && V[i].x == x)
        {

            if (V[index].e >= V[i].s)
                V[index].e = max(V[index].e, V[i].e);

            else
            {
                res.push_back(V[index]);
                index++;
                if (index != n)
                    V[index] = V[i];
            }
            ++i;
        }
        cout << endl
             << endl;

        res.push_back(V[index]);
        index = i;
        x = V[i].x;
    }

    if (index != n)
        res.push_back(V[index]);
    V.clear()
        // debug
        print_V(res);
    cout << endl;
    int ret = 0;
    for (int i = 0; i < res.size(); ++i)
        ret += res[i].e - res[i].s;

    return ret;
}

class Solution
{
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
    {
        if (ax1 == bx1 && ay1 == by1 && ax2 == bx2 && ay2 == by2)
            return (ax2 - ax1) * (ay2 - ay1);
        vector<line> V;
        split(ax1, ay1, ax2, ay2, V);
        split(bx1, by1, bx2, by2, V);
        // debug
        cout << endl
             << endl;
        print_V(V);

        return merge(V);
    }
};

int main()
{
    Solution S;
    cout << S.computeArea(-2, -2, 2, 2, -2, -4, 2, -2) << endl;
}
//-2 - 2 2 2 - 2 - 4 2 - 2