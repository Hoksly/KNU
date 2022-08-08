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

long merge(vector<triple> &V)
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

    long DIV = 10e9 + 7;
    long ret = 0;
    for (int i = 0; i < res.size(); ++i)
    {
        ret += res[i].end - res[i].beg;
        ret %= DIV;
    }

    return ret;
}

class Solution
{
public:
    int rectangleArea(vector<vector<int>> &rectangles)
    {
        vector<triple> splited;
        split(rectangles, splited);
        return merge(splited);
    }
};

// Driver program
int main()
{

    vector<vector<int>> V = {{0, 0, 1000000000, 1000000000}};
    Solution s;
    cout << "Merged: " << s.rectangleArea(V) << endl;
}
