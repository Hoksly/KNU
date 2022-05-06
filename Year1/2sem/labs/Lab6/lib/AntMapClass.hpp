#pragma once
#include <string.h>
#include <vector>
#include "TypesAndDefinitions.hpp"
#include "functions.hpp"

struct AntMap
{
    uchar n;
    int **DistanceMap;
    double **FeromonMap;

    void recalculate_feromon(std::vector<std::vector<uchar>> &V);
    void recalculate_feromon(uchar **Pathes, int);

    void add_feromon(std::vector<uchar> &path);
    void add_feromon(uchar *path);

    void evaporate_feromon();

    int calculate_path(std::vector<uchar> &path, const int &n); // just because we already know n
    int calculate_path(uchar *path);

    void add_feromon_to_road(const uchar i, const uchar j, double v);

    AntMap(uchar size, int **m);
    ~AntMap();
};