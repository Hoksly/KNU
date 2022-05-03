#pragma once
#include "TypesAndDefinitions.hpp"
#include <iostream>
#include <cmath>

inline int calc_for_one(int x1, int y1, int x2, int y2);
inline int give_distance(int **matrix, uchar i, uchar j);
inline void calculate_distance(int **to, std::pair<int, int> *what, uchar n);
int **input_matrix(uchar n);
int **input(uchar &n);