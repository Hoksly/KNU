#include <bits/stdc++.h>
using namespace std;

#define ll long long
typedef pair<ll, ll> pl;

inline bool cmp(const pair<long long, long long> &a, const pair<long long, long long> &b)
{
    return (a.second > b.second);
}
struct myComp
{
    constexpr bool operator()(
        pl const &a,
        pl const &b) const noexcept
    {
        return a.first > b.first;
    }
};

class Solution
{
public:
    long long maxScore(vector<int> &nums1, vector<int> &nums2, int k)
    {
        int n = nums1.size();
        vector<pl> ess(n);
        for (int i = 0; i < n; ++i)
            ess[i] = {nums2[i], nums1[i]};

        sort(rbegin(ess), rend(ess));
        long long totalSum = 0, res = 0;
        priority_queue<int, vector<int>, greater<int>> pq; // min heap
        for (auto &[num1, num2] : ess)
        {
            pq.emplace(num2);
            totalSum += num2;
            if (pq.size() > k)
            {
                totalSum -= pq.top();
                pq.pop();
            }

            if (pq.size() == k)
                res = max(res, totalSum * num1);
        }
        return res;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> v1(n);
    vector<int> v2(n);

    for (int &a : v1)
        cin >> a;
    for (int &a : v2)
        cin >> a;

    Solution s;
    cout << s.maxScore(v1, v2, 3) << endl;
}