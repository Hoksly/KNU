#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

inline void print(const bool *map, const size_t &n)
{
    for (size_t i = 0; i < n; ++i)
        cout << ((map[i]) ? '1' : '0');
    cout << '\n';
}

vector<string> generateCode(int n)
{
    if (n == 1)
    {
        vector<string> res(2);
        res[0] = "0";
        res[1] = "1";
        return res;
    }
    else
    {
        vector<string> prevs = generateCode(n - 1);
        int sz = prevs.size();
        for (int i = 0; i < sz; ++i)
        {
            prevs.push_back(prevs[sz - i - 1] + "1");
            prevs[sz - i - 1] += "0";
        }
        return prevs;
    }
}

int main()
{
    int n;
    cin >> n;
    for (string s : generateCode(n))
        cout << s << '\n';
}