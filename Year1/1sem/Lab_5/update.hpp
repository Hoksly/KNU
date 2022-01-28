#pragma once

#include "classes.hpp" 
#include "functions.hpp"


int update_values(std::vector<Person*> &people,  std::vector<std::pair<std::string, std::string>> to_update);
int command_update(str_with_pos &ch,  std::vector<Person*> &people, int &i);