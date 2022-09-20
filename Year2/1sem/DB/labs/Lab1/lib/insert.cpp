#include "insert.hpp"
#include <iostream>
using namespace std;

template <typename master_T>
int _insert_provider_dev(master_T dev_pr, char index_filename[] = "data/S.ind", char data_filename[] = "data/S.fl")
{
    FILE *datafile, *tmp;

    // for some reason fseek will not work correctly with file opend for writing

    datafile = fopen(data_filename, "r+b");
    if (!datafile)
        datafile = fopen(data_filename, "w+b");
    std::cout << "HERE" << endl;
    fseek(datafile, 0L, SEEK_END);
    int index = ftell(datafile) / sizeof(master_T);
    std::cout << "HERE2" << endl;
    dev_pr.position = index;
    std::cout << "HERE3" << endl;
    fwrite(&dev_pr, sizeof(master_T), 1, datafile);
    fclose(datafile);
    insert_index(index, dev_pr.pv.code_p, index_filename);
}

int insert_provider(int code, const char *surname, const char *city)
{
    provider prov(code, surname, city);
    _provider_dev dev_prov(prov);

    _insert_provider_dev(dev_prov);

    return 0;
}

int _insert_delivery_dev(_delivery_dev del_dev, const char *index_filename, const char *data_filename)
{
}

int insert_delivery(int provide_code, int detail_code, int quantity, int price)
{
}