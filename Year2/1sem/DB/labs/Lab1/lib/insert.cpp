#include "insert.hpp"
#include <iostream>
#include <string.h>
using namespace std;

int insert_master(_provider_dev dev_pr, const char *index_filename, const char *data_filename)
{

    FILE *datafile, *tmp;

    // for some reason fseek will not work correctly with file opend for writing

    // datafile = fopen(data_filename, "r+b");
    if (access(data_filename, F_OK) == 0)
        datafile = fopen(data_filename, "r+b");
    else
        datafile = fopen(data_filename, "w+b");

    if (get_m(dev_pr.master.code))
        return 1; // master already exist

    fseek(datafile, 0L, SEEK_END);
    int index = ftell(datafile) / sizeof(_provider_dev);

    dev_pr.position = index;

    fwrite(&dev_pr, sizeof(_provider_dev), 1, datafile);
    fclose(datafile);

    insert_index(index, dev_pr.master.code, index_filename);
    return 0;
}

int insert_slave(_delivery_dev *slave, const char *slave_filename, const char *master_datafilename, const char *master_indexfilename)
{
    // cout << "SLAVE INSERTION: " << slave->master.code_p << ' ' << slave->master.code_d << endl;
    _provider_dev *prov = get_m_dev(slave->master.code_p, master_indexfilename, master_datafilename);

    if (!prov)
        return 1; // no such master

    _delivery_dev *last_deliv = find_last_slave(prov->first_delivery);

    FILE *datafile;
    datafile = fopen(slave_filename, "r+b");
    if (!datafile)
        datafile = fopen(slave_filename, "w+b");

    fseek(datafile, 0L, SEEK_END);
    int index = ftell(datafile) / sizeof(_delivery_dev);

    slave->index = index;
    if (last_deliv)
    {

        last_deliv->next_ind = index;
        slave->prev_ind = last_deliv->index;
    }

    fwrite(slave, sizeof(_delivery_dev), 1, datafile);

    // in case we have last delivery we need to update it
    if (last_deliv)
        _update_delivery_dev(last_deliv);

    // if no update master first
    else
    {
        // cout << "MASTER " << prov->master.code << " IS CHANGING TO " << index << endl;
        prov->delivery_count = 0;
        prov->first_delivery = index;
        // cout << "CHANGED: " << prov->first_delivery << endl;
    }

    prov->delivery_count++;

    if (last_deliv)
        delete last_deliv;

    _update_provider_dev(prov);
    delete prov;
    fclose(datafile);

    return 0;

    // cout << "END" << endl;
}

int insert_provider(int code, const char *surname, const char *city)
{
    provider prov(code, surname, city);
    _provider_dev dev_prov(prov);

    return insert_master(dev_prov, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);
}

int insert_delivery(int provide_code, int detail_code, int quantity, int price)
{

    _delivery_dev deliv_dev(delivery(provide_code, detail_code, quantity, price));
    return insert_slave(&deliv_dev, SLAVE_FILE, PROVIDERS_DATA_FILE, PROVIDERS_INDEX_FILE);
}
