#pragma once
#include "Classes.hpp"

template <typename master_T>
void get_last_master(const char *filename, master_T *&ret);
_provider_dev *get_last_provider_dev(const char *filename);
_delivery_dev *get_last_delivery_dev(const char *filename);