#pragma once
#include "Classes.hpp"
#include "Constants.hpp"
#include "get.hpp"

void _update_detail_dev(_provider_dev *);
void _update_provider_dev(_provider_dev *);
void _update_delivery_dev(_delivery_dev *);

int update_slave(int, int, int, int, char);
int update_master(int code, std::string sur, std::string city, char option);