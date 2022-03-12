#pragma once
#include <cstdlib>
#include "const.h"
#include "classes.h"
#include<vector>
#include <cstring>
#include <stdio.h>
#include <ctype.h>
#include <iostream>

char * GiveStr(int len);

std::pair<std::vector<std::vector<String*>>, std::vector<std::vector<char>>> give_set(int i);
