#pragma once
#include "lib/AntClass.hpp"
#include "lib/AntMapClass.hpp"
#include "lib/TypesAndDefinitions.hpp"
#include "lib/functions.hpp"
#include <fstream>

uchar **gather(Ant *mas);
uchar *run(Ant *Ants, AntMap &Map, uchar n);
std::vector<std::pair<std::pair<double, double>, int>> test(Ant *Ants, AntMap &Map, uchar n);
double GiveLen(double alpha, double beta, AntMap &Map, int generations, int ant_n, double evap_const, double init_fer, double fer_per_ant);
