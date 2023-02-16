#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void print(vector<long long> &s)
{
    if (s.size() == 0)
    {
        cout << "Empty";
    }

    for (long long i : s)
        cout << i << ' ';
    cout << endl;
}

long long search(vector<long long> &apples, vector<long long> &box1, vector<long long> &box2)
{
    if (apples.size() == 0)
    {
        return abs(accumulate(box1.begin(), box1.end(), 0LL) - accumulate(box2.begin(), box2.end(), 0LL));
    }
    else
    {
        long long apple = apples[apples.size() - 1];
        apples.pop_back();
        box1.push_back(apple);

        long long res1 = search(apples, box1, box2);

        box1.pop_back();
        box2.push_back(apple);
        long long res2 = search(apples, box1, box2);
        box2.pop_back();
        apples.push_back(apple);

        return min(res1, res2);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<long long> apples(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> apples[i];
    }
    vector<long long> box1, box2;

    cout << search(apples, box1, box2) << endl;
}