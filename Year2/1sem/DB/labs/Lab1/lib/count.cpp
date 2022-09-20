#include "count.hpp"

template <typename master_T>
int count_masters(char *filename, master_T not_a_pointer_master)
{
    FILE *file = fopen(filename, "rb");

    fseek(file, 0L, SEEK_END);

    return ftell(file) / sizeof(master_T);
}

int count_slaves(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    fseek(file, 0L, SEEK_END);

    return ftell(file) / sizeof(_delivery_dev);
}

_provider_dev *get_last_provider_dev(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    fseek(file, 0L, SEEK_END);
    if (ftell(file) == 0)
    {
        return nullptr;
    }

    rewind(file);
    _provider_dev *ret = new _provider_dev;
    fseek(file, sizeof(_provider_dev), SEEK_END);

    fread(ret, sizeof(_provider_dev), 1, file);

    return ret;
}

_delivery_dev *get_last_delivery_dev(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    fseek(file, 0L, SEEK_END);
    if (ftell(file) == 0)
    {
        return nullptr;
    }

    rewind(file);
    _delivery_dev *ret = new _delivery_dev;
    fseek(file, sizeof(_delivery_dev), SEEK_END);

    fread(ret, sizeof(_delivery_dev), 1, file);

    return ret;
}
