#include <iostream>
#include <cmath>
#include <ctime>


using namespace std;


double f1(double x)
{
    return sin(x);
}

double f2(double x)
{
    return sin(x)*cos(2*x);
}

double f3(double x)
{
    return pow(sin(x)*sin(2*x), 2);
}

auto g = [] (auto f_test,auto f ,double a, double b, int step, int increase, double eps)
{
    while(fabs(f_test(f, a, b, step) - f_test(f, a, b, step*increase)) > eps)
        {
            step *= increase;
            cout << "step" << endl;
        }
    return step;
};



const double eps_def = 1e-4;
double trapezoid(double (*f) (double), double a, double b, double eps_beg=0.01)
{
    
    double res = 0;
    for(double i = a; i < b; i+= eps_beg)
    {
        res += (((f(i)+f(i+eps_beg)))*eps_beg);
    }

    res /= 2;

    return res;

}

double simpson(double (&f) (double), double a, double b, double eps)
{
    double res = 0;
    double eps_2 = eps/2;
    for(double i = a; i < b; i+= eps)
    {
        res += f(i) + 4*f(i + eps_2) + f(i+eps);
    }
    res *= eps;
    res /= 6;
    return res;
}


double gous(double (&f) (double), double a, double b, double eps)
{
    double res = 0;
    double eps_2 = eps/2;
    double eps_sq = eps/(2* sqrt(3));
    for(double i = a; i < b; i+= eps)
    {
        res += f(i+eps_2 - eps_sq) + f(i+eps_2 + eps_sq);
    }

    res *= (eps/2);
    return res;

}


/*
void check()
{
    const double a = 0, b = 1000;
    cout.precision(16);
    time_t t = time(NULL);
    cout << "from "<< a << " to " << b << endl;

    cout << "Method1: Gaus" << endl;
    cout << "Method2: Trapezoid" << endl;
    cout << "Method3: Simpson" << endl;
    cout << "steps: " << (b-a) / eps << endl << endl;
    
    cout << "sin(x)" << endl;

    cout << gous(f1, a, b) << endl;
    //cout << "time gaus: " << t- clock() <<endl;
    t = clock();
    cout << trapezoid(f1, a, b)<< endl;
    //cout << "time trapezoid: " << t- clock() <<endl;
    t = clock();
    cout << simpson(f1, a, b) << endl;
    //cout << "time simpson: " << t- clock() <<endl;
    t = clock();

    cout << endl << endl;

    cout << "sin(x)*cos(2*x)" << endl;

    cout << gous(f2, a, b) << endl;
    //cout << "time gaus: " << t- time(NULL) <<endl;
    t = time(NULL);
    cout << trapezoid(f2, a, b)<< endl;
    //cout << "time trapezoid: " << t- time(NULL) <<endl;
    t = time(NULL);
    cout << simpson(f2, a, b) << endl;
    //cout << "time simpson: " << t- time(NULL) <<endl;
    t = time(NULL);

    cout << endl << endl;

    cout << "(sin(x) * sin(2*x)) ^ 2" << endl;

    cout << gous(f3, a, b) << endl;
    //cout << "time gaus: " << t- time(NULL) <<endl;
    t = time(NULL);
    cout << trapezoid(f3, a, b)<< endl;
    //cout << "time trapezoid: " << t- time(NULL) <<endl;
    t = time(NULL);
    cout << simpson(f3, a, b) << endl;
    //cout << "time simpson: " << t- time(NULL) <<endl;
    t = time(NULL);






}
*/

int main()
{

    cout << g(trapezoid, f1, 0, 100, 10, 2, 1e-4) << endl;   

}