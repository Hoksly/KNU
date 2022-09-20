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