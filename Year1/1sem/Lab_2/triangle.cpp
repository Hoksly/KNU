#include <iostream>
#include <cmath>

// n == 4


using namespace std;


struct line{
    // ax + by + c = 0
    double a;
    double b;
    double c;
};

struct point{
    double x;
    double y;
    double z;
    double t;

};


struct triangle{
    point a;
    point b;
    point c;

    double l_ab;
    double l_ac;
    double l_bc;

    
    point center;

};


pair<double, double> solve_equasion(line l1, line l2)
{
    double y = ((-1 * l1.c * l2.a) - (l2.c * l1.a) / (l2.a * l1.b + l2.b));
    double x = (l1.b * y + l1.c) / l1.a;
    pair <double, double> ret;
    ret.first = x;
    ret.second = y;

    return ret;
}

pair <double, double> operator-(pair<double, double> b, pair<double, double> a)
{
    pair <double, double> f;
    f.first = b.first - a.first;
    f.second = b.second - a.second;
    return f;
}

triangle take_input()
{
    triangle ret;

    cin >> ret.a.x >> ret.a.y >> a.z >> a.t;
    cin >> ret.b.x >> ret.b.y >> b.z >> b.t;
    cin >> ret.c.x >> ret.c.y >> c.z >> c.t;


    
    return ret;
}

double sq(double a)
{
    return a*a;
}

double calc_len(point a, point b)
{
    double res;

    res = sqrt(sq(a.x - b.x) + sq(a.y - b.y) + sq(a.z - b.z) + sq(a.t - b.t));
    return ret;

}

void calc_lens_in_triangle(triangle A)
{

    A.l_ab = calc_len(A.a, A.b);
    A.l_ac = calc_len(A.a, A.c);
    A.l_bc = calc_len(A.c, A.b);

}



bool are_similar(triangle A, triangle B)
{
    

    return false;
}

int main()
{
    //triangle A = take_input();

    //triangle B = take_input();
    line l1, l2;
    l1.a = -2; l1.b = 5; l1.c = 6;
    l1.a = 8; l2.b = 3; l2.c = -6;

    pair<double, double> res = solve_equasion(l1, l2);
    cout.precision(16);
    cout << res.first << ' ' << res.second << endl;




}