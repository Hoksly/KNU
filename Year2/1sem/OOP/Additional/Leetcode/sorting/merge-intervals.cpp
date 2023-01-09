#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end());
        int curBeg = intervals[0][0], curEnd = intervals[0][1];
        vector<vector<int>> res;

        for (int i = 1; i < intervals.size(); ++i)
        {
            if (curEnd < intervals[i][0])
            {
                vector<int> newInterval(2);
                newInterval[0] = curBeg;
                newInterval[1] = curEnd;
                res.push_back(newInterval);

                curBeg = intervals[i][0];
                curEnd = intervals[i][1];
            }
            else
                curEnd = intervals[i][1];
        }
        vector<int> newInterval(2);
        newInterval[0] = curBeg;
        newInterval[1] = curEnd;
        res.push_back(newInterval);
        return res;
    }
};

int main()
{
    vector<vector<int>> v = {{1, 4}, {0, 4}};

    Solution s;
    for (vector<int> m : s.merge(v))
    {
        cout << m[0] << ' ' << m[1] << endl;
    }

    return 0;
}