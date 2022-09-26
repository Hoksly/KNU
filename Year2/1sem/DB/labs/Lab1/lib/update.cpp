#include "update.hpp"

void _update_provider_dev(_provider_dev *prov_dev)
{
    FILE *file;
    file = fopen(PROVIDERS_DATA_FILE, "r+b");
    fseek(file, (prov_dev->position * sizeof(_provider_dev)), 0);
    _provider_dev *pv = new _provider_dev;
    fread(pv, sizeof(_provider_dev), 1, file);
    // std::cout << "READING: " << pv->first_delivery << " TELLING: " << ftell(file) << '\n';
    // std::cout << "CODE: " << pv->master.code << " POSTION: " << pv->position << '\n';
    // std::cout << "OTHER CODE: " << prov_dev->master.code << std::endl;

    rewind(file);
    fseek(file, (prov_dev->position * sizeof(_provider_dev)), 0);
    fwrite(prov_dev, sizeof(_provider_dev), 1, file);
    fclose(file);
}

// update linking between slaves and master
void _update_delivery_dev(_delivery_dev *slave)
{
    FILE *file = fopen(SLAVE_FILE, "r+b");

    fseek(file, sizeof(_delivery_dev) * slave->index, 0);
    fwrite(slave, sizeof(_delivery_dev), 1, file);
    fclose(file);
}