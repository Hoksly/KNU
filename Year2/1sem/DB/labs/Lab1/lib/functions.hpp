#pragma once
#include <algorithm>
int search(int code, char *filename);
void change_index(int code, int new_index, char filename[] = "data/S.ind");
void remove_index_record(int code, char filename[] = "data/S.ind");
void insert_index(int index, int code, char filename[] = "data/S.ind");