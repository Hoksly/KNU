#include "del.hpp"

void del_m_dev(int code, const char *data_filename, const char *index_filename)
{

    // first of all, need to check if this record exist!!!

    _provider_dev *prov_to_del, *last;

    prov_to_del = get_m_dev(code, index_filename, data_filename);

    last = get_last_provider_dev(data_filename);

    if (!prov_to_del)
        return;

    FILE *file = fopen(data_filename, "r+b");

    if (prov_to_del->master.code != last->master.code)
    {
        int indx = search(code, index_filename);

        fseek(file, sizeof(_provider_dev) * indx, 0);
        fwrite(last, sizeof(_delivery_dev), 1, file);

        change_index(code, indx, index_filename);
        remove_index_record(code, index_filename);
    }

    fseek(file, 0L, SEEK_END);
    // deliting last record, works only in Linux
    truncate(data_filename, ftell(file) - sizeof(_provider_dev));
    fclose(file);

    delete last, prov_to_del;
}

void del_provider(int code)
{
    del_m_dev(code, PROVIDERS_DATA_FILE, PROVIDERS_INDEX_FILE);
}

void del_detail(int code)
{
    del_m_dev(code, PROVIDERS_DATA_FILE, PROVIDERS_INDEX_FILE);
}

_provider_dev *get_slave(int slave_index, int seek_begin = SEEK_SET)
{
    if (slave_index == -1)
        return nullptr; // just in case ...

    FILE *file = fopen(SLAVE_FILE, "r+b");

    fseek(file, index * sizeof(_delivery_dev), seek_begin);

    _delivery_dev *del_dev = new _delivery_dev;
    fread(del_dev, sizeof(_delivery_dev), 1, file);

    fclose(file);
    return del_dev;
}
inline void remove_slave(int index)
{
    _delivery_dev *del_dev = get_slave(index);

    int rm_index = del_dev->index;
    _provider_dev *master = get_m_dev(del_dev->master.code_p, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);

    if (master->first_delivery != rm_index)
    {
        _delivery_dev *previous = get_slave(del_dev->prev_ind);
        previous->next_ind = del_dev->next_ind;

        delete previous;
    }
    else
    {
        master->first_delivery = del_dev->next_ind;
    }
}

void delete_slaves(int slave_index)
{

    FILE *file = fopen(SLAVE_FILE, "r+b");

    if (!file)
        return;

    do
    {
        rewind(file);
        fseek(file, slave_index * sizeof(_delivery_dev), 0);

    } while (/* condition */);
}