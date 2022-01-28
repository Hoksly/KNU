#include <iostream>
#include <cmath>

using namespace std;

double factorial(int n) {
    double f = 1;
    for (int i = 2; i <= n; i++) {
        f *= i;
    }
    return f;
}

double eval(int n) {
    return pow(-2, n) / factorial(n);
}

int main() {
    double sum = 0,  eps;

    cin >> eps;

    double prev = 0;
    for (int n = 0; ; n++) {
       double res = eval(n);
       sum += res;
       if(fabs(res) < eps) break;
       prev = res;
    }

    cout << sum << endl;
    //system("pause");
    return 0;
}