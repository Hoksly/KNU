#pragma once
#include "Classes.hpp"
#include "functions.hpp"
#include <stdio.h>

provider *get_m(int code);
delivery *get_s(int, int, char[]);
_provider_dev *get_m_dev(int code, char *ind_filename, char *data_filename);
_delivery_dev *get_s_dev(int detail_code, int provider_code, char *filename);