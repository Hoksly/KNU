#pragma once
#include <fstream>
#include <vector>
#include <iostream>

#include "Classes.hpp"
#include "Constants.hpp"

int search(int code, char *filename);
void change_index(int code, int new_index, char filename[] = "data/S.ind");
void remove_index_record(int code, char filename[] = "data/S.ind");
void insert_index(int index, int code, char filename[] = "data/S.ind");
_delivery_dev *find_last_slave(int first_slave_index);