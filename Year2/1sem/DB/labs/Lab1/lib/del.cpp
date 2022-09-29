#include "del.hpp"
using namespace std;

_delivery_dev *get_slave(int slave_index, int seek_begin = 0)
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

void delete_slaves_but_not_actully_delete(int first_slave_index)
{
    FILE *file = fopen(SLAVE_FILE, "r+b");
    _delivery_dev *slave;
    if (!file)
        return;

    do
    {
        rewind(file);
        slave = get_slave(first_slave_index);
        if (!slave)
            return;
        slave->alive = 0;
        _update_delivery_dev(slave);
        first_slave_index = slave->next_ind;

    } while (first_slave_index);
}

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
    delete_slaves_but_not_actully_delete(prov_to_del->first_delivery);

    fclose(file);

    delete last, prov_to_del;
}

int del_provider(int code)
{
    provider *master = get_m(code);
    if (master)
    {
        // del_m_dev(code, PROVIDERS_DATA_FILE, PROVIDERS_INDEX_FILE);
        _provider_dev *master = get_m_dev(code, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);
        del_m_dev(code, PROVIDERS_DATA_FILE, PROVIDERS_INDEX_FILE);

        delete master;
        return 0;
    }
    return 1;
}

void del_detail(int code)
{
    del_m_dev(code, PROVIDERS_DATA_FILE, PROVIDERS_INDEX_FILE);
}

_delivery_dev *get_last_slave()
{

    FILE *file = fopen(SLAVE_FILE, "r+b");

    fseek(file, 0L, SEEK_END);
    int last_index = ftell(file) / sizeof(_delivery_dev) - 1;
    rewind(file);

    _delivery_dev *slave = new _delivery_dev;

    fseek(file, last_index * sizeof(_delivery_dev), 0);
    fread(slave, sizeof(_delivery_dev), 1, file);
    cout << "Last " << slave->index << endl;
    return slave;
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

    _delivery_dev *previous;

    _delivery_dev *slave_to_remove = get_slave(index);

    _provider_dev *master = get_m_dev(slave_to_remove->master.code_p, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);

    link_master_previous_and_next_slaves(slave_to_remove);

    _delivery_dev *last = get_last_slave();
    // print_slave(last);
    //  our slave_to_remove is not linked with other, but we need to write it over

    if (true)
    {

        _provider_dev *master_of_last = get_m_dev(last->master.code_p, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);
        master_of_last->first_delivery = index;

        _delivery_dev *next, *previous;
        previous = get_slave(last->prev_ind);
        next = get_slave(last->next_ind);

        if (previous)
        {

            previous->next_ind = (last->index == slave_to_remove->index) ? -1 : index;
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
    else
    {
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
    _delivery_dev *slave;
    if (!file)
        return;

    do
    {
        rewind(file);
        slave = get_slave(slave_index);
        remove_slave(slave_index);
        slave_index = slave->next_ind;

    } while (slave_index);
}

int rm_slave(int code_p, int code_d)
{
    FILE *file = fopen(SLAVE_FILE, "rb");
    _delivery_dev *slave = new _delivery_dev;
    if (!file)
        return 2; // error while opening file

    while (!feof(file))
    {
        fread(slave, sizeof(_delivery_dev), 1, file);

        if (slave->master.code_d == code_d && slave->master.code_p == code_p)
        {

            fclose(file);
            cout << "slave index: " << slave->index << endl;
            remove_slave(slave->index);
            delete slave;
            return 0;
        }
    }
    return 1; // no such slave
}

int rm_slave_old(int code_p, int code_d)
{
    {
        FILE *file = fopen(SLAVE_FILE, "rb");
        _delivery_dev *slave = new _delivery_dev;
        if (!file)
            return 2; // error while opening file

        while (!feof(file))
        {
            fread(slave, sizeof(_delivery_dev), 1, file);

            if (slave->master.code_d == code_d && slave->master.code_p == code_p)
            {

                fclose(file);
                slave->alive = 0;
                _update_delivery_dev(slave);
                delete slave;
                return 0;
            }
        }
        return 1; // no such slave
    }
}

void clear_master_trash()
{
    FILE *master_file = fopen(PROVIDERS_DATA_FILE, "rb");

    _provider_dev *master = new _provider_dev;
    while (!feof(master_file))
    {
        fread(master, sizeof(_provider_dev), 1, master_file);
        if (!master->alive)
        {
            del_m_dev(master->master.code, PROVIDERS_DATA_FILE, PROVIDERS_INDEX_FILE);
            fseek(master_file, master->position * sizeof(_provider_dev), 0);
        }
    }
    delete master;
    fclose(master_file);
}

void clear_slave_trash()
{
    using std::cout;

    FILE *slave_file = fopen(SLAVE_FILE, "rb");

    _delivery_dev *slave = new _delivery_dev;
    while (!feof(slave_file))
    {
        fread(slave, sizeof(_delivery_dev), 1, slave_file);
        if (!slave->alive)
        {
            rm_slave_old(slave->master.code_p, slave->master.code_d); // actual remove
            fseek(slave_file, slave->index * sizeof(_delivery_dev), 0);
        }
    }
    delete slave;
    fclose(slave_file);
}