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

_delivery_dev *get_slave(int slave_index, int seek_begin = SEEK_SET)
{
    if (slave_index == -1)
        return nullptr; // just in case ...

    FILE *file = fopen(SLAVE_FILE, "r+b");

    fseek(file, slave_index * sizeof(_delivery_dev), seek_begin);

    _delivery_dev *del_dev = new _delivery_dev;
    fread(del_dev, sizeof(_delivery_dev), 1, file);

    fclose(file);
    return del_dev;
}

inline bool is_first(_delivery_dev *slave)
{
    // return true if our slave is first in the linked list

    _provider_dev *master = get_m_dev(slave->master.code_d, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);
    bool res = false;
    if (master->first_delivery == slave->index)
        res = true;
    delete master;
    return res;
}

inline void link_master_previous_and_next_slaves(_delivery_dev *middle_slave)
{
    _provider_dev *master = get_m_dev(middle_slave->master.code_p, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);

    _delivery_dev *previous, *next;
    previous = get_slave(middle_slave->prev_ind);
    next = get_slave(middle_slave->next_ind);

    if (previous) // so previous item exist
    {
        previous->next_ind = middle_slave->next_ind;

        if (next)
        {
            next->prev_ind = previous->index;
            _update_delivery_dev(next);
        }

        _update_delivery_dev(previous);
    }
    else // so our miidle slave is first slave in the list
    {
        if (next) // our next slave will become first
        {
            master->first_delivery = next->index;
            next->prev_ind = -1;
        }
        else // so no other slave exist
        {
            master->first_delivery = -1;
        }
    }

    master->delivery_count -= 1;
    _update_provider_dev(master);

    delete master;
    if (next)
        delete next;
    if (previous)
        delete previous;
}

inline void remove_slave(int index)
{
    _delivery_dev *slave_to_del, *previous;

    _delivery_dev *slave_to_remove = get_slave(index);

    _provider_dev *master = get_m_dev(slave_to_remove->master.code_p, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);

    link_master_previous_and_next_slaves(slave_to_remove);

    _delivery_dev *last = get_slave(1, SEEK_END);

    // our slave_to_remove is not linked with other, but we need to write it over
    if (last->index != slave_to_del->index) // so we have more than one slave in file
    {
        _provider_dev *master_of_last = get_m_dev(last->master.code_p, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);
        master_of_last->first_delivery = index;

        _delivery_dev *next, *previous;
        previous = get_slave(last->prev_ind);
        next = get_slave(last->next_ind);

        if (previous)
        {
            previous->next_ind = index;
            if (next)
            {
                next->prev_ind = index;
                _update_delivery_dev(next);
            }
            _update_delivery_dev(previous);
        }
        else // so our item is first in linked list
        {
            master_of_last->first_delivery = index;
            if (next)
            {
                next->prev_ind = index;
                _update_delivery_dev(next);
            }
            _update_provider_dev(master_of_last);
        }
    }

    FILE *slave_file = fopen(SLAVE_FILE, "r+b");
    fseek(slave_file, index * sizeof(_delivery_dev), 0);
    fwrite(last, sizeof(_delivery_dev), 1, slave_file);

    rewind(slave_file);
    fseek(slave_file, 0L, SEEK_END);
    // deliting last record, works only in Linux
    truncate(SLAVE_FILE, ftell(slave_file) - sizeof(_delivery_dev));

    fclose(slave_file);
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