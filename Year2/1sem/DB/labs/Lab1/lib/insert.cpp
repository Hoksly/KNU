#include "insert.hpp"
#include <iostream>
using namespace std;

template <typename master_T>
int insert_master(master_T dev_pr, char index_filename[] = "data/S.ind", char data_filename[] = "data/S.fl")
{
    FILE *datafile, *tmp;

    // for some reason fseek will not work correctly with file opend for writing

    datafile = fopen(data_filename, "r+b");
    if (!datafile)
        datafile = fopen(data_filename, "w+b");

    fseek(datafile, 0L, SEEK_END);
    int index = ftell(datafile) / sizeof(master_T);

    dev_pr.position = index;

    fwrite(&dev_pr, sizeof(master_T), 1, datafile);
    fclose(datafile);
    insert_index(index, dev_pr.pv.code_p, index_filename);
}

void insert_slave(_delivery_dev *slave, char *slave_filename, char *master_datafilename, char *master_indexfilename)
{
    _provider_dev *prov = get_m_dev(slave->dv.code_p, master_indexfilename, master_datafilename);
    _delivery_dev *last_deliv = find_last_slave(prov->position);

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

    _update_provider_dev(prov);
    // in case we have last delivery we need to update it
    if (last_deliv)
    {
        rewind(datafile);
        fseek(datafile, sizeof(_delivery_dev) * last_deliv->index, 0);
        fwrite(last_deliv, sizeof(_delivery_dev), 1, datafile);
    }
    // if no update master first
    else
    {
        prov->delivery_count = 0;
        prov->first_delivery = index;
    }

    prov->delivery_count++;

    if (last_deliv)
        delete last_deliv;

    delete prov;
    fclose(datafile);
}

int insert_provider(int code, const char *surname, const char *city)
{
    provider prov(code, surname, city);
    _provider_dev dev_prov(prov);

    insert_master(dev_prov, "data/S.ind", "data/S.fl");

    return 0;
}

int insert_delivery(int provide_code, int detail_code, int quantity, int price)
{
}

int insert_detail(int code, const char *name, int mas, const char *color, const char *city)
{
    detail det(code, name, mas, color, city);
    _detail_dev det_dv(det);

    insert_master(det_dv, "data/D.ind", "data/D.fl");
}

int _insert_detail_dev(_detail_dev dt_dev, char *data_dilename, char *index_filename)
{
}