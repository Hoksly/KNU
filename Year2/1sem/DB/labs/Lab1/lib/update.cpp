#include "update.hpp"

void _update_provider_dev(_provider_dev *prov_dev)
{
    FILE *file;
    file = fopen(PROVIDERS_DATA_FILE, "r+b");

    fseek(file, prov_dev->position * sizeof(_provider_dev), 0);

    fwrite(prov_dev, sizeof(_provider_dev), 1, file);
    fclose(file);
}

// update linking between slaves and master
void _update_delivery_dev(_delivery_dev *slave)
{
}