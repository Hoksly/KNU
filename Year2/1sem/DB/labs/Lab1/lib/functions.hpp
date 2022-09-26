#pragma once
#include <fstream>
#include <vector>
#include <iostream>

#include "Classes.hpp"
#include "Constants.hpp"

int search(int code, const char *filename);
void change_index(int code, int new_index, const char *filename);
void remove_index_record(int code, const char *filename);
void insert_index(int index, int code, const char *filename);
_delivery_dev *find_last_slave(int first_slave_index);

void print_slave(_delivery_dev *slave);
void print_all_slaves();