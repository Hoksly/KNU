#include <iostream>
#include <vector>
using namespace std;

int give_step_2(int n)
{   
    int res = 0;
    if(n == 0 || n == 1)
        return 1;
    while(n > 0)
    {
        n /= 2;
        res++;
    }

    return res;
}
long long pow(long long a, long long step)
{    if(step == 0)
        return 1;

    if(step % 2 == 1)
        return a*pow(a, step-1);

    return pow(a*a, step/2);
}
long long give_great_number_by_n(int n)
{
    // n - amount of 1 in binary form of number
    // n = 3 => 11100 => 28
    long long res = 0;
    if(n == 1)
        return 1LL;
    n--;
    for(int i = 0; i <= n; i++)
    {
        res += pow(2LL, n+i);
        //cout << res << endl;
    }

    return res;
}
bool check_number(int n)
{
    int res = 0;
    for(int i = 1; i <= n/2; i++)
    {
        if(n%i == 0)
            res+=i;
    }
    //cout << res << ' ' << n << endl;
    return (res == n);
}
void task_search_great_numbers()
{
    long long n;
    int end, sz;

    cin >> n;
    int step = give_step_2(n);
    end = (step+1)/2 + 1;
    vector<long long> All;
    for(int i = 1; i < end; i++)
    {
        All.push_back(give_great_number_by_n(i));
    }
    sz = All.size();
    cout << sz << endl;
    for(int i = 0 ; i < sz; i++)
    {
        if(check_number(All[i]))
            cout << All[i] << endl;
    }

    

}

/*
Tests:
inp:

10000000000

out:
16
6
28
496
8128
33550336
*/

int main()
{

    task_search_great_numbers();
    return 0;
}