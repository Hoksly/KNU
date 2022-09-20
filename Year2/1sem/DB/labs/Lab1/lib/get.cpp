#include "get.hpp"

inline provider *clean_dev(_provider_dev *prov)
{
    provider *ret = new provider;
    *ret = prov->master;
    return ret;
}

_provider_dev *get_m_dev(int code, const char *ind_filename, const char *data_filename)
{

    long index = search(code, ind_filename);

    if (index == -1)
    {

        return nullptr;
    }

    _provider_dev *to_find = new _provider_dev;

    FILE *data_file = fopen(data_filename, "rb");

    long struc_porition = fseek(data_file, sizeof(_provider_dev) * index, 0);

    fread(to_find, sizeof(provider), 1, data_file);

    fclose(data_file);

    provider *ret = clean_dev(to_find);

    return to_find;
}

provider *get_m(int code)
{
    _provider_dev *dv = get_m_dev(code, "data/S.ind", "data/S.fl");
    if (!dv)
        return nullptr;

    provider *ret = clean_dev(dv);

    delete dv;
    return ret;
}

inline _delivery_dev *get_delivery_by_index(int indx, FILE *&file)
{

    _delivery_dev *ret = new _delivery_dev;

    rewind(file);
    fseek(file, sizeof(_delivery_dev) * indx, 0);
    fread(ret, sizeof(_delivery_dev), 1, file);

    return ret;
}

inline _delivery_dev *next_delivery(const _delivery_dev *deliv, FILE *&file)
{
    if (deliv->next_ind == -1)
        return nullptr;

    return get_delivery_by_index(deliv->next_ind, file);
}

inline delivery *clean_deliv_dev(_delivery_dev *dev)
{
    delivery *ret = new delivery;

    *ret = dev->master;
    return ret;
}

_delivery_dev *get_s_dev(int detail_code, int provider_code, const char *filename)
{

    int count, first_index = -1;

    _provider_dev *prov = get_m_dev(provider_code, "data/S.ind", "data/S.fl");
    first_index = prov->position;
    count = prov->delivery_count;

    FILE *deliv_file = fopen(filename, "rb");
    _delivery_dev *deliv, *tmp;

    deliv = get_delivery_by_index(first_index, deliv_file);

    while (deliv)
    {
        if (deliv->master.code_d == detail_code)
            break;

        tmp = next_delivery(deliv, deliv_file);
        delete deliv;
        deliv = tmp;
    }

    return deliv;
}

delivery *get_s(int detail_code, int provider_code)
{
    char filename[] = "data/SP.fl";
    _delivery_dev *dv = get_s_dev(detail_code, provider_code, filename);

    if (!dv)
        return nullptr;
    delivery *ret = new delivery;
    *ret = dv->master;

    delete dv;
    return ret;
}