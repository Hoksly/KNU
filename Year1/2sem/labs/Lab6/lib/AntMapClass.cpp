#include "AntMapClass.hpp"
#include "functions.hpp"
using std::vector;

AntMap::AntMap(uchar size, int **m)
{
    DistanceMap = m;
    n = size;
    FeromonMap = new double *[size];
    double *mas;

    for (uchar i = 0; i < size; ++i)
    {
        mas = new double[size];
        set(mas, INIT_FEROMON, size); // idk
        // print_dd(mas, size - i);
        FeromonMap[i] = mas;
    }
}
AntMap::~AntMap()
{
    delete DistanceMap;
    delete FeromonMap;
}

void AntMap::evaporate_feromon()
{
    for (uchar i = 0; i < n; ++i)
    {
        for (uchar j = 0; j < n; ++j)
            FeromonMap[i][j] *= EVOPARTION_CONST;
    }
}

void AntMap::add_feromon_to_road(const uchar i, const uchar j, double v)
{
    FeromonMap[i][j] += v;
    FeromonMap[j][i] += v;
}

int AntMap::calculate_path(uchar *path, uchar mx)
{
    int ret = 0;

    for (uchar i = 1; i < mx; ++i)
        ret += give_distance(DistanceMap, path[i - 1], path[i]);

    return ret;
}

void AntMap::add_feromon(uchar *path)
{
    // std::cout << "RECALC" << '\n';

    double feromon_per_unit = FEROMON_PER_ANT / calculate_path(path, n + 1);
    uchar mx = n + 1; // len of path

    // for (uchar i = 0; i < mx; ++i)
    // std::cout << path[i] << ' ';
    // std::cout << '\n';

    for (uchar i = 1; i < mx; ++i)
    {
        // for (uchar i = 0; i < mx; ++i)
        // std::cout << path[i] << ' ';
        // std::cout << '\n';
        uchar a, b;
        a = path[i - 1];
        b = path[i];
        // std::cout << "Cur: " << i << ' ' << path[i - 1] << ' ' << path[i] << '\n';
        //  std::cout << feromon_per_unit << '\n';
        give_distance(DistanceMap, a, b);
        add_feromon_to_road(a, b, give_distance(DistanceMap, path[i - 1], path[i]) * feromon_per_unit);
    }
}

void AntMap::recalculate_feromon(uchar **Pathes, int ants_n)
{
    for (int i = 0; i < ants_n; ++i)
        add_feromon(Pathes[i]);
    evaporate_feromon();
}