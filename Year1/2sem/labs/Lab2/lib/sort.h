#pragma once 

#include <vector>
#include "classes.h"
#include "const.h"
#include <deque>
#include <queue>
#include <iostream>
#include <cstdlib>
#include "utils.h"

std::vector<String *> LecSort(const std::vector<std::vector<char>> &NotEmpty, const std::vector<std::vector<String *>> &len_strings);
void OutSort(char *filename);