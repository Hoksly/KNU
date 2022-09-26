#pragma once
#include "Classes.hpp"
#include "Constants.hpp"
#include "get.hpp"
#include "update.hpp"
#include "count.hpp"
#include <unistd.h>

#include <iostream>
void delete_slaves(int slave_index);
int rm_slave(int code_p, int code_d);
int del_provider(int code);