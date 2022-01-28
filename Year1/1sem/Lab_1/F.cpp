#include <iostream>

using namespace std;

int main ()
{
    long double a, b;
    cin >> a >> b;
    //cout.precision(10);cout<<a<<' '<<int(a)<<' '<<(int)a<<endl;
    int zm = 4;
    while (a - int (a) > 0.000001) {a *= 10; zm *= 10;}
    while (b - int (b) > 0.000001) {b *= 10; zm *= 10;}

    long long int x = a;
    x *= b;

    while (true)
    {
        if (x % 2 == 0 && zm % 2 == 0) {x /= 2; zm /= 2;}
        else if (x % 5 == 0 && zm % 5 == 0) {x /= 5; zm /= 5;}
        else {break;}
    }

    if (zm == 1) {cout << x << endl;}
    else {cout << x << '/' << zm << endl;}

    return 0;
}
