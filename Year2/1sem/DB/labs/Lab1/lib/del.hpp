#pragma once
#include "Classes.hpp"
#include "Constants.hpp"
#include "get.hpp"
#include "update.hpp"
#include "count.hpp"
#include <unistd.h>

#include <iostream>

void delete_slaves(int slave_index);
int del_provider_old(int code);
int del_provider(int code);
int rm_slave(int code_p, int code_d);
int rm_slave_old(int code_p, int code_d);
void delete_slaves_but_not_actully_delete(int first_slave_index);
void clear_slave_trash();

void clear_master_trash();