#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> hanoi(int n, int from, int middle, int to)
{
    if (n == 1)
    {
        return {{from, to}};
    }
    vector<pair<int, int>> movingToMiddle = hanoi(n - 1, from, to, middle);
    movingToMiddle.push_back({from, to});
    vector<pair<int, int>> movingToEnd = hanoi(n - 1, middle, from, to);
    movingToMiddle.insert(movingToMiddle.end(), movingToEnd.begin(), movingToEnd.end());
    return movingToMiddle;
}

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> res = hanoi(n, 1, 2, 3);
    cout << res.size() << '\n';
    for (pair<int, int> p : res)
    {
        // cout << p.first << " -> " << p.second << '\n';
    }
}