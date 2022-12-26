#include <bits/stdc++.h>
using namespace std;

struct triple
{
    int x;
    int beg;
    int end;
    triple(int a, int b, int c) : x(a), beg(b), end(c) {}
};

void slpitone(vector<int> &V, vector<triple> &ret)
{
    // cout << "SPliting" << endl;
    ret.reserve(V[2] - V[0]);
    for (int i = V[0]; i < V[2]; ++i)
    {
        // cout << i << endl;
        triple a(i, V[1], V[3]);
        ret.push_back(a);
    }
    // cout << "Finished" << endl;
}

void split(vector<vector<int>> &V, vector<triple> &ret)
{
    for (vector<int> v : V)
        slpitone(v, ret);
}

// Function used in sort

inline bool comp(triple a, triple b)
{
    if (a.x == b.x)
        return a.beg < b.beg;
    else
        return a.x < b.x;
}

long long merge(vector<triple> &V)
{
    sort(V.begin(), V.end(), comp);

    int index = 0, n = V.size(), x = V[0].x;

    vector<triple> res;

    for (int i = 1; i < n; ++i)
    {
        cout << "Iteration: " << i << endl;
        while (V[i].x == x)
        {
            if (V[index].end >= V[i].beg)
                V[index].end = max(V[index].end, V[i].end);

            else
            {
                res.push_back(V[index]);
                index++;
                if (index != n)
                    V[index] = V[i];
            }
            ++i;
        }

        res.push_back(V[index]);
        index = i;
        x = V[i].x;
    }

    if (index < n)
        res.push_back(V[index]);

    long long DIV = 10e9 + 7;
    long long ret = 0;
    for (int i = 0; i < res.size(); ++i)
    {
        ret += res[i].end - res[i].beg;
        ret %= DIV;
    }

    return ret;
}

long solve(vector<vector<int>> &rec)
{
    vector<triple> rt;
    split(rec, rt);
    return merge(rt);
}

enum EVS
{
    OPEN,
    CLOSE
};

struct event
{
    long long y, x1, x2;
    EVS act;
    event(long long a, EVS e, long long b, long long c)
    {
        y = a;
        act = e;
        x1 = b;
        x2 = c;
    }
};

bool mycmp(const event &a, const event &b)
{
    if (a.y != b.y)
        return a.y < b.y;
    else if (a.act != b.act)
        return a.act < b.act;
    else if (a.x1 != b.x1)
        return a.x1 < b.x1;

    return a.x2 < b.x2;
}

long long query(vector<pair<long long, long long>> &active)
{
    long long ans = 0, cur = -1;
    for (pair<long long, long long> act : active)
    {
        cur = max(cur, act.first);
        ans += max((long long)0, act.second - cur);
        cur = max(cur, act.second);
    }
    return ans;
}

const long long DIV = 1000000007;
long long inline norm(long long what)
{
    return ((what + DIV) % DIV);
}

long long linesweep(vector<vector<int>> &rectangles)
{
    vector<event> V;
    V.reserve(rectangles.size() * 2);
    for (vector<int> rectangle : rectangles)
    {
        V.push_back(event(rectangle[1], OPEN, rectangle[0], rectangle[2]));
        V.push_back(event(rectangle[3], CLOSE, rectangle[0], rectangle[2]));
    }

    auto print_message = [](std::string message) {

    };

    sort(V.begin(), V.end(), mycmp);

    vector<pair<long long, long long>> active;
    long long cur_y = V[0].y;
    long long ans = 0;

    for (event ev : V)
    {
        ans += norm(query(active)) * norm(ev.y - cur_y);

        ans = norm(ans);

        if (ev.act == OPEN)
        {
            active.push_back(make_pair(ev.x1, ev.x2));
            sort(active.begin(), active.end());
        }
        else
            active.erase(find(active.begin(), active.end(), make_pair(ev.x1, ev.x2)));

        cur_y = ev.y;
    }

    return ans;
}

class Solution
{
public:
    int rectangleArea(vector<vector<int>> &rectangles)
    {
        return linesweep(rectangles);
    }
};

int main()
{

    vector<vector<int>> V = {{49, 40, 62, 100}, {11, 83, 31, 99}, {19, 39, 30, 99}};
    Solution s;
    cout << "Merged: " << endl
         << s.rectangleArea(V) << endl;
}
