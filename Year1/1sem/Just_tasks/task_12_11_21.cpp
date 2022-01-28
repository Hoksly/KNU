#include <iostream>
#define ll long long



ll accer_3(int N, int X, int Y)
{
    if(N == 0)
        return X+1;
    if(Y == 0)
    {
        if(N == 1)
            return (ll) X;
        if(N == 2)
            return 0LL;
        if(N == 3)
            return 1LL;
        if(N == 4)
            return 2LL;

    }
    return accer_3(N-1, accer_3(N, X, Y-1), X);

}

ll acer_2(int M, int N)
{
    if(M == 0)
        return n+1;
    if (N == 0)
        return accer_2(M-1, 1);

}



int max_n_left(int *mas, int beg = 0, int n)
{
    if (beg == n-1)
        return mas[beg];

    return min(mas[beg], max_n(mas, ++beg, n));
    
}

int max_n_right(int *mas, int n)
{
    if(n == 1)
        return mas[n-1];
        
    return min(mas[n-1], max_n_right(mas, n-1));
}

void take_input(int &N, int &X, int &Y)
{
    std::cin >> N >> X >> Y;
}

template <class X>
void print_out(X a)
{   
    try{std::cout << a << std::endl;}
    catch(...){}

}



int main()
{
    int N, X, Y;
    take_input(N, X, Y);
    print_out(accer_3(N, X, Y));
    
    
}
