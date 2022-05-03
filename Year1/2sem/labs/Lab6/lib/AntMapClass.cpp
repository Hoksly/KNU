#include "AntMapClass.hpp"
#include "functions.hpp"
using std::vector;

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

inline void AntMap::add_feromon_to_road(uchar i, uchar j, double v)
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
        add_feromon_to_road(path[i - 1], path[i], give_distance(DistanceMap, path[i - 1], path[i]) * feromon_per_unit);
    }
}

void AntMap::recalculate_feromon(vector<vector<uchar>> &Pathes)
{
    for (vector<uchar> path : Pathes)
        add_feromon(path);
    evaporate_feromon();
}