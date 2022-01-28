#pragma once
#include "classes.hpp"
#include "functions.hpp"

std::string give_selected_results(std::vector<Person*> &printed, std::vector<std::string> params);

int command_select(str_with_pos &ch,  std::vector<Person*> &people, int &i);