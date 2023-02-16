#include <iostream>

using namespace std;

long long fPow(long long base, long long step, long long mod)
{
    long long ans = 1;
    while (step > 0)
    {

        if (step % 2)
        {
            ans *= base;
            ans %= mod;
            --step;
        }
        else
        {
            base *= base;
            base %= mod;
            step /= 2;
        }
    }
    return ans;
}

int main()
{
    long long n;
    cin >> n;
    cout << fPow(2LL, n, 1000000007LL) << endl;
}