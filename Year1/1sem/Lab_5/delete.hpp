#pragma once 

#include "functions.hpp"
#include "classes.hpp"

int delete_person(std::vector<Person*> &people, std::vector<Person*> &to_delete);

int delete_command(str_with_pos &ch,  std::vector<Person*> &people, int &i);