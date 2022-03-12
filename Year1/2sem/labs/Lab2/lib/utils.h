#pragma once

#include "classes.h"
#include "const.h"
#include <vector>
#include <string.h>
#include <iostream>

std::vector<std::vector<std::pair<int, char>>> ToPairs(std::vector<std::vector<String*>> Strings);
void ConvertToNonEpty(std::vector<std::vector<std::pair<int, char>>> &What, std::vector<std::pair<int, char>*> &To);
std::vector<std::pair<int, char>*> CreateNotEpty(std::vector<std::vector<std::pair<int, char>>> &What);
std::vector<std::vector<String *>> ToLenStrings(char **mas, int n);
std::vector<std::vector<char>> ToNotEmpty(const std::vector<std::vector<String *>> &Strings);

