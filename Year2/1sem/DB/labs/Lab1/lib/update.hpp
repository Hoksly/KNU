#pragma once
#include "Classes.hpp"
#include "Constants.hpp"

void update_slave(_delivery_dev *dv_dev, char *filename = SLAVE_FILE);
void _update_detail_dev(_provider_dev *);
void _update_provider_dev(_provider_dev *);