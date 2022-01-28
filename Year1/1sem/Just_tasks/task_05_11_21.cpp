#include <iostream>
#include <cstring>
#define ll long long

const int MAX_BITS = 256;
const int MAX_LINE_SIZE = 128;
const int MAX_SIZE_SIMPLE_MAS = 1000000;
using namespace std;
char * take_inp_string()
{
    char *line = new char[MAX_LINE_SIZE];
    std::cin >> line; 
    return line;
}

bool * create_bitmap(char * S)
{
    int sz = strlen(S);
    bool *map = new bool[MAX_BITS];
    memset(map, 0, MAX_BITS);

    for(int i = 0; i < sz; i++)
        map[S[i]] = true;
    return map;
}

std::pair<bool, int> find_first(char * S, char * T)
{
    
    bool * map = create_bitmap(T);
    int sz = strlen(S);
    for(int i = 0; i < sz; i++)
        if(!map[(int) S[i]])
            {   //cout << S[i] << endl;
                return  std::make_pair(true, i);}

    return std::make_pair(false, 0);
}

void print_out(bool res, int i)
{
    if(res)
    {
        std::cout << "Errror at index " << i << '\n';
    }
    else
    {
        std::cout << "Evrything allright" << '\n';
    }
}

bool * generate_n_simple(ll n)
{
    int sz = n / 2;
   
    bool *map = new bool[n];
    memset(map, 1, n);
    for(int i = 2; i < sz; i++)
    {
        if(map[i])
        {   
            
            for(int j = i*2; j< sz; j+=i)
            {
                map[j] = false;
            }
        }
    }
    return map;
}
ll * generate_mas(ll n, int &sz)
{

    sz = 0;
    bool *bit_map = generate_n_simple(n);
    ll mx = n/2+1;
    for(ll i = 0LL; i < mx; i++)
    {
        sz += bit_map[i];
    } 

    ll *mas = new ll[sz];
    sz = 0;
    for(ll i = 0LL; i < mx; i++)
    {
        if(bit_map[i])
            {mas[sz] = i; sz++;}
    }

    return mas;

}


int bin_search(ll * mas, ll target, int sz)
{
    int l = -1;
    int r = sz;
    int mid = (l+r)/2;

    while(r-l > 1)
    {
        mid = (l+r) /2 ;
        if(mas[mid] > target)
            l = mid;
        else if (mas[mid] < target)
            r = mid;
        else 
            return mid;

    }

    return (l+r)/2;
}


std::pair<ll, ll> solve(ll n)
{
    ll h = n/2LL;
    int sz;
    ll *mas = generate_mas(n, sz);
    std::cout << bin_search(mas, 10000, sz);
   
}

int main()
{
    char *S = take_inp_string();
    char *T = take_inp_string();

    std::pair<bool, int> res = find_first(S, T);
    print_out(res.first, res.second);

}