#include <iostream>

using namespace std;
long long pow(long long x, long long base)
{
    long long ans = 1;
    while (base > 0LL)
    {
        --base;
        ans *= x;
    }
    return ans;
}

int main()
{

    string s;
    cin >> s;
    long long n = s.size();
    long long problemID = 0;

    for (int i = 0; i < n; ++i)
    {

        problemID += pow(26LL, n - i - 1) * ((long long)s[i] - 'A' + 1LL);
    }
    cout << problemID << endl;
    return 0;
}