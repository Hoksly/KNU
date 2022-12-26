#include <vector>
#include <iostream>
using namespace std;

int MOD = 1337;

inline int myPow(int a, int n, int mod = 1337)
{
    if(n == 0)
        return 1;
    if (n % 2 == 1)
        return (a % mod) * (myPow(a, n-1, mod) % mod) % mod;

    return myPow((a*a) % mod, n/2, mod) % mod;
}

class Solution {
public:
    int superPow(int a, vector<int>& b) {
        int res = 1;
        if (a % MOD == 0)
            return 0;
        int dynamicPow = a % 1337;
        
        res *= myPow(dynamicPow, b[b.size()-1]);
        res %= MOD;
    
        for (int i = b.size()-2; i > -1; --i)
        {
            cout << b[i] << ' ' << dynamicPow << std::endl;
            dynamicPow = myPow(dynamicPow, 10);    
            res *= myPow(dynamicPow, b[i]);
            res %= MOD;
        }

        return res;

    }
};

int main()
{
    Solution s;
    vector<int> b = {1, 0};
    cout << s.superPow(2, b) << endl;
}