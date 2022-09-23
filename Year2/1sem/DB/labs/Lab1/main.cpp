#include "lib/get.hpp"
#include "lib/insert.hpp"
#include "lib/update.hpp"
#include <iostream>
#define MASTER_INDEX_FILE "data/S.ind"
#include <fstream>
#include <vector>
#define MASTER_DATA_FILE "data/S.fl"

using namespace std;

struct tmp_detail
{
    int i, mas;
    string s1, s2, s3;
};

struct tmp_provider
{
    int code;
    string s1, s2;
};

struct delivery_raw_data
{
    int code_p, code_d, q, p;
};

void instert_details_from_file(string filename = "SampleData/Details.txt")
{

    ifstream file;

    file.open(filename);
    vector<tmp_detail> V;

    tmp_detail tt;
    while (!file.eof())
    {

        file >> tt.i >> tt.s1 >> tt.mas >> tt.s2 >> tt.s3;

        V.push_back(tt);
    }
    V.pop_back();
    for (tmp_detail a : V)
    {
        insert_detail(a.i, a.s1.c_str(), a.mas, a.s2.c_str(), a.s3.c_str());
    }
}

void insert_providers_from_file(string filename = "SampleData/Providers.txt")
{

    ifstream file;

    file.open(filename);
    vector<tmp_provider> V;

    tmp_provider tt;
    while (!file.eof())
    {

        file >> tt.code >> tt.s1 >> tt.s2;

        V.push_back(tt);
    }

    V.pop_back();

    for (tmp_provider a : V)
    {
        insert_provider(a.code, a.s1.c_str(), a.s2.c_str());
    }
}

void insert_slaves_from_file(string filename = "SampleData/Delivery.txt")
{
    ifstream file;

    file.open(filename);
    vector<delivery_raw_data> V;

    delivery_raw_data tt;
    while (!file.eof())
    {

        file >> tt.code_p >> tt.code_d >> tt.q >> tt.p;

        V.push_back(tt);
    }
    V.pop_back();

    for (delivery_raw_data a : V)
    {
        insert_delivery(a.code_p, a.code_d, a.q, a.p);
    }
}

int main()
{
    // insert_providers_from_file();
    //  insert_slaves_from_file();

    delivery *slave = get_s(1, 1);

    if (!slave)
        cout << "FUCK" << endl;

    cout << "PRINTING" << endl;
    cout << slave->code_d << ' ' << slave->code_p << endl;
    cout << slave->price << ' ' << slave->quantity << endl;
}