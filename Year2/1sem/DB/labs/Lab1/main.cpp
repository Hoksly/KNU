#include "lib/get.hpp"
#include "lib/insert.hpp"
#include "lib/update.hpp"
#include "lib/del.hpp"
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
/*
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
*/

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

void read_and_insert_slave()
{
    cout << "Provide slave information" << endl;
    int provider_code, detail_code, quantity, price;
    cout << "Provider code: ";
    cin >> provider_code;
    cout << "Detail code: ";
    cin >> detail_code;
    cout << "Quantity: ";
    cin >> quantity;
    cout << "Provider code: ";
    cin >> price;

    int res = insert_delivery(provider_code, detail_code, quantity, price);
    switch (res)
    {
    case 0:
        cout << SUCCESSFUL_MESAGE << endl;
        break;
    case 1:
        cout << NO_SUCH_MASTER << endl;
        break;
    case 2:
        cout << SLAVE_EXIST << endl;
        break;
    }
}

void read_and_insert_master()
{
    cout << "Provide master information" << endl;
    int provider_code;
    std::string surname, city;

    cout << "Provider code: ";
    cin >> provider_code;
    cout << "Provider surname: ";
    cin >> surname;
    cout << "Provider city: ";
    cin >> city;

    int res = insert_provider(provider_code, surname.c_str(), city.c_str());

    switch (res)
    {
    case 0:
        cout << SUCCESSFUL_MESAGE << endl;
        break;
    case 1:
        cout << NO_SUCH_MASTER << endl;
    case 2:
        cout << SLAVE_EXIST << endl;
    }
}

void read_and_delete_slave()
{
    int provider_code, detail_code;
    cout << "Provider code: ";
    cin >> provider_code;
    cout << "Detail code: ";
    cin >> detail_code;

    int res = rm_slave(provider_code, detail_code);

    switch (res)
    {
    case 0:
        cout << SUCCESSFUL_MESAGE << endl;
        break;
    case 1:
        cout << NO_SUCH_SLAVE << endl;
    case 2:
        cout << FILE_ERROR << endl;
    }
}

void read_and_delete_master()
{
    int master_code;
    cout << "Master code: ";
    cin >> master_code;

    int res = del_provider(master_code);

    switch (res)
    {
    case 0:
        cout << SUCCESSFUL_MESAGE << endl;
        break;
    case 1:
        cout << NO_SUCH_MASTER << endl;
    }
}

void read_and_update_slave()
{

    cout << "Provide slave to update information" << endl;
    int provider_code, detail_code, quantity, price;

    cout << "Provider code: ";
    cin >> provider_code;

    cout << "Detail code: ";
    cin >> detail_code;

    cout << QUANT_OR_PRICE << endl;
    char key;
    cin >> key;
    int res;
    switch (key)
    {
    case 'q':
        cout << "Quantity: ";
        cin >> quantity;
        res = update_slave(provider_code, detail_code, quantity, price, key);
        break;
    case 'p':
        cout << "Price: ";
        cin >> price;
        res = update_slave(provider_code, detail_code, quantity, price, key);
        break;

    default:
        cout << INVALID_OPTION_EXIT << endl;
        return;
    }

    if (res == 1)
        cout << NO_SUCH_SLAVE << endl;
    if (res == 0)
        cout << SUCCESSFUL_MESAGE << endl;
}

void read_and_update_master()
{
    cout << "Provide master to update information";
    int provider_code;
    std::string sur, city;
    cout << "Provider code: ";
    cin >> provider_code;

    cout << SUR_OR_CITY << endl;
    char key;
    cin >> key;
    switch (key)
    {
    case 's':
        cout << "Surname (max 20): ";
        cin >> sur;
        update_master(provider_code, sur, city, key);
        break;
    case 'c':
        cout << "City (max 20): ";
        cin >> city;
        update_master(provider_code, sur, city, key);
        break;

    default:
        cout << INVALID_OPTION_EXIT << endl;
        return;
    }
}

void get_and_display_master()
{

    int provider_code;
    _provider_dev *master;
    cout << "Provider code: ";
    cin >> provider_code;
    master = get_m_dev(provider_code, PROVIDERS_INDEX_FILE, PROVIDERS_DATA_FILE);

    if (!master)
        cout << NO_SUCH_MASTER << endl;
    else
        print_master(master);
}

void get_and_display_slave()
{
    int provider_code, detail_code;
    _delivery_dev *slave;

    cout << "Provider code: ";
    cin >> provider_code;
    cout << "Detail code: ";
    cin >> detail_code;

    slave = get_s_dev(provider_code, detail_code, SLAVE_FILE);
    if (!slave)
    {
        cout << NO_SUCH_SLAVE << endl;
        return;
    }
    print_slave(slave);
}

void display_all_slaves()
{
    print_all_slaves();
}

void display_all_masters()
{
    print_all_masters();
}

void display_help()
{
    cout << HELP_MESSAGE << endl;
}
void display_slave_help()
{
    cout << MASTER_OR_SLAVE << endl;
}

void display_interupted()
{
    cout << "Operation interapted" << endl;
}

void run_interactive_mode()
{
    display_help();
    char key;
    while (true)
    {
    FIRST_WHILE:

        cin >> key;
        switch (key)
        {
        case 'i':
            while (true)
            {
                display_slave_help();

                cin >> key;

                switch (key)
                {
                case 's':
                    read_and_insert_slave();
                    goto FIRST_WHILE;
                case 'm':
                    read_and_insert_master();
                    goto FIRST_WHILE;
                case 'b':
                    display_interupted();
                    goto FIRST_WHILE;
                }
            }
            break;

        case 'd':
            display_slave_help();

            cin >> key;

            switch (key)
            {
            case 's':
                read_and_delete_slave();
                goto FIRST_WHILE;
            case 'm':
                read_and_delete_master();
                goto FIRST_WHILE;
            case 'b':
                display_interupted();
                goto FIRST_WHILE;
            }
            break;

        case 'u':
            display_slave_help();

            cin >> key;

            switch (key)
            {
            case 's':
                read_and_update_slave();
                goto FIRST_WHILE;
            case 'm':
                read_and_update_master();
                goto FIRST_WHILE;
            case 'b':
                display_interupted();
                goto FIRST_WHILE;
            } /* code */
            break;

        case 'g':
            display_slave_help();

            cin >> key;

            switch (key)
            {
            case 's':
                get_and_display_slave();
                goto FIRST_WHILE;
            case 'm':
                get_and_display_master();
                goto FIRST_WHILE;
            case 'b':
                display_interupted();
                goto FIRST_WHILE;
            }
            break;

        case 'h':
            display_help();
            break;

        case 'm':
            display_all_masters();
            break;
        case 's':
            display_all_slaves();
            break;

        case 'e':
            return;

        default:
            cout << INVALID_OPTION << endl;
            display_help();

            break;
        }
    }
    clear_master_trash();
    clear_slave_trash();
}

int main()
{
    // insert_providers_from_file();
    // insert_slaves_from_file();

    run_interactive_mode();
}
/*

*/