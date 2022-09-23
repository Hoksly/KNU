#pragma once
#include "Classes.hpp"
#include "functions.hpp"
#include "update.hpp"
#include "get.hpp"
#include <stdio.h>
#include <unistd.h>

int insert_provider(int code, const char *surname, const char *city);
void insert_detail(int code, const char *name, int mas, const char *color, const char *city);
void insert_delivery(int provide_code, int detail_code, int quantity, int price);