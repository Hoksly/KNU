#include <iostream>

using namespace std;


int cos_sm( double x, double accuracy =1e-15)
{
    int n = 1;
    double pr_fact = 1;
    double pr_step = 1;

    double res = 0;
    double new_app = 1;

    while (abs(new_app) > accuracy)
    {
        res += new_app;

        new_app = (pr_step * x * x) / (pr_fact * (2*n));
        new_app = (n % 2 == 0) ? new_app: -1*new_app;
        pr_step *= x*x;
        pr_fact *= 2*n;
        n+=1;
        //cout << n << ' ' << (new_app) <<' ' << res << endl;

    }

    cout << res << endl;
    return res;
    
}

int  sin_sm( double x, double accuracy =1e-15)
{
    // not working
    int n = 1;
    double pr_fact = 1;
    double pr_step = x;

    double res = x;
    double new_app = 0;

    do{
        res += new_app;
        pr_step *= x*x;
        pr_fact *= (2*n+1);

        new_app = pr_step / pr_fact ;
        
        new_app = (n % 2 == 0) ? new_app: -1*new_app;
        
        n+=1;
        //cout << n << ' ' << (new_app) <<' ' << res << endl;


    }
    while (abs(new_app) > accuracy);


    cout << res << endl;
    return res;
    
}



int main()
{

    double x, accuracy;
    //cin >> x >> accuracy;
    cin >> x;
    double res = sin_sm(x);
    cout.precision(16);
    //cout << res << endl;
}