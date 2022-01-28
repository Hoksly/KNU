#include <iostream>

using namespace std;    

long double res_find(long double x, long double a, long double eps)
{   bool res = x < eps;

    cout << res << endl;
    if(x < eps)
        return x;

    return  res_find(((x*x)+a) / (2*x), a, eps);

    

}

long double sqr(long double a, long double eps = 0.00000001)
{

    long double x = (a<5)? 2: a/2;

    return res_find(x, a, eps);
    

}


int main()
{
    //5
    // block == a*b*c, window == d*e
   
    /*
    bool res;
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e; 
    res = (a*b < d*e) || (a*c < d*e) || (b*c < d*e);

    cout << res << endl;
    */


   long double a;
   cin >> a;
   cout.precision(16);
   cout << sqr(a);

}