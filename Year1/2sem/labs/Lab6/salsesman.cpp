#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned char uchar; // used mostly for matrix sizes

inline int calc_for_one(int x1, int y1, int x2, int y2)
{
    return (int)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

inline int give_distance(int **matrix, uchar i, uchar j) // because we use a triangle matrix...
{
    return (i < j) ? matrix[i][j - i] : matrix[j][i - j]; // should we control a i == j situation? Just in case of human factor...
}

inline void calculate_distance(int **to, pair<int, int> *what, uchar n)
{
    // also it creates a matrix to

    for (uchar i = 0; i < n; ++i)
    {
        to[i] = new int[n - i];
        for (uchar j = i + 1; j < n; ++j)
        {
            to[i][j - i] = calc_for_one(what[i].first, what[i].second, what[j].first, what[j].second);
        }
    }
}

int **input_matrix(uchar n)
{
    int **res = new int *[n], a, x, y;
    pair<int, int> *V = new pair<int, int>[n];

    for (uchar i = 0; i < n; ++i)
    {
        cin >> a >> x >> y;
        V[i].first = x;
        V[i].second = y;
    }

    calculate_distance(res, V, n);
    return res;
}

int **input(uchar &n)
{
    int p;
    cin >> p;
    n = p;

    return input_matrix(n);
}

int main()
{
    int **Matrix;
    uchar n;

    Matrix = input(n);
    cout << give_distance(Matrix, 1, 28) << endl;
}