#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>

using namespace std;

const int ALPHA = 1;
const int BETA = 1;
const double FEROMON_PER_ANT = 1;
const double EVOPARTION_CONST = 0.5;
const double INIT_FEROMON = 0.2;

typedef unsigned char uchar; // used mostly for matrix sizes

// function prototypes
inline int calc_for_one(int x1, int y1, int x2, int y2);
inline int give_distance(int **matrix, uchar i, uchar j);
inline void calculate_distance(int **to, pair<int, int> *what, uchar n);
int **input_matrix(uchar n);
int **input(uchar &n);

struct AntMap
{
    uchar n;
    int **DistanceMap;
    double **FeromonMap;
    void recalculate_feromon(vector<vector<uchar>> &V);

    void add_feromon(vector<uchar> &path);
    void evaporate_feromon();
    int calculate_path(vector<uchar> &path, const int &n); // just because we already know n

    inline void add_feromon(uchar i, uchar j, double v);

    AntMap(uchar size, int **m);
};

AntMap::AntMap(uchar size, int **m)
{
    DistanceMap = m;
    FeromonMap = new double *[size];
    double *mas;

    for (uchar i = 0; i < size; ++i)
    {
        mas = new double[size - i];
        memset(mas, INIT_FEROMON, size - i);
        FeromonMap[i] = mas;
    }
}
void AntMap::evaporate_feromon()
{
    for (uchar i = 0; i < n; ++i)
    {
        for (uchar j = i + 1; j < n; ++j)
            FeromonMap[i][j] *= EVOPARTION_CONST;
    }
}

inline void AntMap::add_feromon(uchar i, uchar j, double v)
{
    if (i > j)
        FeromonMap[j][i] += v;
    else
        FeromonMap[i][j] += v;
}

int AntMap::calculate_path(vector<uchar> &path, const int &n)
{
    int ret = 0;
    for (int i = 1; i < n; ++i)
        ret += give_distance(DistanceMap, path[i - 1], path[i]);

    return ret;
}

void AntMap::add_feromon(vector<uchar> &path)
{
    int s = path.size();
    double feromon_per_unit = FEROMON_PER_ANT / calculate_path(path, s);
    for (int i = 1; i < s; ++i)
    {
        add_feromon(path[i - 1], path[i], give_distance(DistanceMap, path[i - 1], path[i]) * feromon_per_unit);
    }
}

void AntMap::recalculate_feromon(vector<vector<uchar>> &Pathes)
{
    for (vector<uchar> path : Pathes)
        add_feromon(path);
}

struct Ant
{
    vector<uchar> path;
    uchar current_node;
};

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
    // AntMap Map(Matrix);

    // cout << give_distance(Matrix, 1, 28) << endl;
}