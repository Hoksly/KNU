#pragma once
#include <vector>
#include "classes.hpp"
#include <stdio.h>
#include <iostream>

int read_file(const char *filename, std::vector<Person*> *people);
int write_in_file(const char *filename, std::vector<Person*> *people);