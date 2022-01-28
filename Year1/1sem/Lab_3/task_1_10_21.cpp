#include <iostream>
#include <vector>
using namespace std;


void task_1()
{
    int a;
    cin >> a;
    vector <int> A;

    while (a > 0)
    {
        A.push_back(a%2);
        a /= 2;
    }
    int n = A.size();
    for(int i = 0; i < n; i++)
    {
        cout << A[i] << ' ';
    }
    cout << endl;

    bool pol = true;
    int end = n/2 + n%2+1;
    n -= 1;
    for(int i = 0; i < end; i++)
    {
        if(A[i] != A[n-i])
            pol = false;
    }

    string res = (pol)? "YES":"NO";
    cout << res << endl;


    cout << endl;
}




void insert_new_element(int A[100], int size,  int new_el)
{
    int new_pos = 0;
    for(; new_pos<size; new_pos++)
    {
        if(A[new_pos] > new_el)
            break;
    }

    //1 2 3 4 (5) 6

    for(int i = size-1; i >= new_pos; i--)
    {
        A[i] = A[i-1];
    }

    A[new_pos] = new_el;


}




double newton_sqrt(double a)
{
    double mas[1000];
    mas[0];
}

auto f1()
{
    cout << "Hello ";
}
/*
auto f = [](){return "Hello ";};

auto g = [](auto f, auto s2) {return f() + s2;};

auto c = [](auto f, auto g, auto s){return g(f, s) + '\n';};
*/


auto f = [](auto x) {return x+3;};
auto g = [](auto f, auto x) {return f(x) * f(x);};

int main()
{
    cout << g(f, 7) << endl;

}