//
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <iostream>
#define ll long long

//const unsigned int MAX_VALUE = 2147483646; 
const unsigned int MAX_VALUE = 10000; //I changed this value, because creataing bitmap was a very slow process 
bool * erat(unsigned int n)
{   
    // creating a bitmam for simple(?) numbers
    n++;
    bool * map = new bool[n];
    memset(map, true, n);
    map[0] = map[1] = false;
    for (int i = 2; i < n; i++)
    {
        //std::cout << i << '\n';
        if(map[i])
            for(int j = i*2; j < n; j+= i)
                map[j] = false;
        
    }

    return map;
}

ll rec_search(unsigned int *mas, unsigned n, bool *bitmap)
{
    //std::cout << n << '\n';
    if (n == 0)
        return (bitmap[mas[0]])? mas[0]: 0LL;
    if(bitmap[mas[0]])
        std::cout << mas[n] << '\n';

    return (bitmap[mas[n]])? mas[n] + rec_search(mas, n-1, bitmap): rec_search(mas, n-1, bitmap);    
}


unsigned int *input_mas_1D(unsigned int &n)
{
    std::cin >> n;
    unsigned int *mas = new unsigned int[n];
    for(int  i = 0; i < n; i++)
        std::cin >> mas[i];
    return mas;
}

template<class X>
void print_res(X n)
{
    try
    {
        std::cout << n << '\n';
    }
    catch(const std::exception& e)
    {
        std::cout << "Error occured when printing result" << '\n';
        std::cerr << e.what() << '\n';
    }
    
}

int main()
{
    bool *bitmap = erat(MAX_VALUE);
    unsigned int n;

    unsigned int *mas = input_mas_1D(n);
    ll res = rec_search(mas, n, bitmap);

    print_res(res);    

    //unsigned long long = rec_search();


    return 0;
}

/*
12
1 0 2 1 4 3 5 7 9 1 9 2

19
*/