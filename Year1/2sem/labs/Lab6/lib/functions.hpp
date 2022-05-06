#pragma once
#include "TypesAndDefinitions.hpp"
#include <iostream>
#include <cmath>

// DEBUG
void print_mas(bool *mas, int n);
void print_d(double **mas, int n);
void print_i(int **mas, int n);
void print_dd(double *mas, int n);

void set(double *mas, double what, int n);
void set(bool *mas, bool what, int n);

inline int calc_for_one(int x1, int y1, int x2, int y2)
{
    return (int)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

inline int give_distance(int **matrix, uchar i, uchar j)
{
    return matrix[i][j];
}
inline double give_feromon(double **matrix, uchar i, uchar j)
{
    return matrix[i][j];
}
inline void calculate_distance(int **to, std::pair<int, int> *what, uchar n)
{
    // also it creates a matrix to
    for (uchar i = 0; i < n; ++i)
        to[i] = new int[n];
    for (uchar i = 0; i < n; ++i)
    {
        for (uchar j = i + 1; j < n; ++j)
        {
            // std::cout << to[i] << '\n';
            to[i][j] = to[j][i] = calc_for_one(what[i].first, what[i].second, what[j].first, what[j].second);
            // std::cout << to[i][j - i] << '\n';
        }
    }
}
int **input_matrix(uchar);
int **input(uchar &);
