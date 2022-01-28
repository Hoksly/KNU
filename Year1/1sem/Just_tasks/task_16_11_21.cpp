#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;


double f1(double x)
{
    return x*x*x - 2*x + 1;
}


double rec_search(double l, double r, double eps, double (*f) (double),  double target = 0)
{
    
    if (fabs(l - r) < eps)
        cout << l << ' ' << r << endl;
        return (l+r) / 2;
    
    double mid = (l+r) / 2;
    if (f(mid) < 0.0)
        { cout << "here1" << endl;
            return rec_search(mid, r, eps, f, target);}
    
    else
       {cout << "here2" << endl;
           return rec_search(l, mid, eps, f, target);}
    
    
}

void print_sol(double *mas, char *oper, int n)
{
    n--;
    /* for(int i = 0; i < n;mas++, oper++)
        cout << *mas << *oper;
    cout << *mas << endl;*/
    cout << "printing n: " << n << endl;


}
double find_value(double *mas, char *oper, int r, int l)
{
    if (r == l)
        return mas[r];
    if (oper[r] == '+')
        return mas[r] + find_value(mas, oper, r+1, l);
    if (oper[r] == '-')
        return mas[r] - find_value(mas, oper, r+1, l);
    if (oper[r] == '/')
        return mas[r] / find_value(mas, oper, r+1, l);
    if (oper[r] == '*')
        return mas[r] * find_value(mas, oper, r+1, l);
    
    
}
double new_val_left(char oper, double l, double r)
{
    switch (oper)
    {
    case '+':
        return l - r;
    case '-':
        return l + r;
    case '*':
        return l / r;
    case '/':
        return l * r;
    default:
        return l;
    
    }

}

double new_val_right(char oper, double l, double r)
{
    switch (oper)
    {
    case '+':
        return l + r;
    case '-':
        return l - r;
    case '*':
        return l * r;
    case '/':
        return l / r;
    
    }

}

void find_eq(double left, double right, double *mas, char *oper, int pos, int n, double target)
{
    cout << pos << endl;
    if (pos < 1)
        return;
    if(left + right == target)
        {
        oper[pos-1] = '+';
        print_sol(mas, oper, n);
        }
    
    if(left - right == target)
        {
        oper[pos-1] = '-';
        print_sol(mas, oper, n);
        }
    if(left * right == target)
        {
        oper[pos-1] = '*';
        print_sol(mas, oper, n);
        }
    if(left / right == target)
        {
        oper[pos-1] = '/';
        print_sol(mas, oper, n);
        }
    
    if (pos == 1)
        return;
    
    oper[pos-1] = '+';
    char *ms = new char[n];
    strcpy(ms, oper);
    double n_left = new_val_left(oper[pos-1], left, mas[pos]);
    double n_right = new_val_right(oper[pos], left, mas[pos]); 
    find_eq(n_left, n_right, mas, ms, pos-1, n, target);

    oper[pos-1] = '-';
    
    strcpy(ms, oper);
    n_left = new_val_left(oper[pos-1], left, mas[pos]);
    n_right = new_val_right(oper[pos], left, mas[pos]); 
    find_eq(n_left, n_right, mas, ms, pos-1, n, target);
    

    oper[pos-1] = '/';
   
    strcpy(ms, oper);
    n_left = new_val_left(oper[pos-1], left, mas[pos]);
    n_right = new_val_right(oper[pos], left, mas[pos]); 
    find_eq(n_left, n_right, mas, ms, pos-1, n, target);

    oper[pos-1] = '*';
    
    strcpy(ms, oper);
    n_left = new_val_left(oper[pos-1], left, mas[pos]);
    n_right = new_val_right(oper[pos], left, mas[pos]); 
    find_eq(n_left, n_right, mas, ms, pos-1, n, target);

// 1 + 2 + 3 + 4 + 5 + 6
}





void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void Q_sort(int *a, int low, int high) {
    int i, j;
    int tmp, pivot;
 
    i = low;
    j = high;
 
    pivot = a[(low + (high-low)/2)];
    do {
        while (a[i] < pivot) {
            i++;
        }
        while (a[j] > pivot) {
            j--;
        }
        if (i <= j) {
            if (a[i] > a[j]) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
            i++;
            if (j > 0) {
                j--;
            }
        }
    } while (i <= j);
 
    if (i < high) {
        Q_sort(a, i, high);
    }
    if (j > low) {
        Q_sort(a, low, j);
    }
}

template<class X>
void take_input(X *mas, int n)
{
    for(int i = 0; i < n; mas++)
        cin >> *mas;
}

template <class X>
void print_out(X *mas, int n)
{
    for(int i = 0; i < n; mas++)
        cout << *mas << ' ';
    cout << endl;
}

int main()
{
    /*int n; 
    cin >> n;
    int *mas = new int[n+1];
    take_input(mas, n);
    Q_sort(mas, 0, n-1);
    print_out(mas, n);

    delete[] mas;
*/


    double mas[7] = {1, 2, 3, 4, 5, 6, 0};
    char oper[6] = {'+', '+', '+', '+', '+', '\0'};
    find_eq(21, 0, mas, oper, 5, 6, 35);
}