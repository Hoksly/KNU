#include <iostream>
#include <cstring>
using namespace std;

const int MAX_LEN_LINE = 150;
const int MAX_LEN_OF_OST = 50;
const int MAX_LEN_INT = 10;

void take_input(int *a)
{
    cin >> *a;
}

bool find_in_mas(int *mas, int sz, int n)
{
    for(int i = 0; i<sz; i++, mas++)
        if(*mas == n)
            return true;
    return false;
}

void solve_task(int *n, char *out)
{
    int *ost = new int[MAX_LEN_OF_OST];
    char *n_str = new char[MAX_LEN_INT];
    //cout << "GG" << endl;
    int i = 1, m, f;
     /*
     for(;i<*n;i*=10)
            {*ost = '0'; ost++;}
    */

    for(int q = 0; q < MAX_LEN_OF_OST; q++, ost++)
    {
        i*= 10;
        for(;i<*n;i*=10)
            {*ost = '0'; ost++;}
        if(find_in_mas(ost, q, i))
            break;
        sprintf(n_str, "%d", i/(*n));
        //cout << "HERE: " <<  i << ' ' << (*n) << endl;
        strcat(out, n_str);
        
        *ost = i;
        
        ost++;
        
        i %= (*n);

    }
    *ost = '\0';
}

int main()
{
    int *n = new int;
    char *out = new char[MAX_LEN_LINE];
    take_input(n);
    solve_task(n, out);
    cout << out << endl;

    delete n;
    delete[] out;  
}