#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "classes.h"
#include "const.h"
#include <fstream>


bool readline(FILE *file, char * ret);
//std::vector<std::vector<String*>> read_file(char* , std::vector<std::vector<char>>);
std::pair<std::vector<std::vector<String*>>, std::vector<std::vector<char>>> read_file(char* );
void write_out(char *filename, std::vector<String *> &sorted);