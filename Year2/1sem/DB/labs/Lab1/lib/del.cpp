#include "del.hpp"

void del_m(int code)
{
}

void del_m_dev(int code, char *data_filename, char *index_filename)
{
    _provider_dev *prov_to_del, *last;

    prov_to_del = get_m_dev(code, index_filename, data_filename);
    last = get_last_provider_dev(data_filename);

    if (!prov_to_del)
        return;

    FILE *file = fopen(data_filename, "r+b");

    if (prov_to_del->pv.code_p != last->pv.code_p)
    {
        int indx = search(code, index_filename);

        fseek(file, sizeof(_provider_dev) * indx, 0);
        fwrite(last, sizeof(_delivery_dev), 1, file);

        change_index(code, indx);
        remove_index_record(code);
    }

    fseek(file, 0L, SEEK_END);
    // deliting last record, works only in Linux
    truncate(data_filename, ftell(file) - sizeof(_provider_dev));
    fclose(file);
}
