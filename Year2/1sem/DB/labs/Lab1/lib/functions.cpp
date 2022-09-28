#include "functions.hpp"

using std::ifstream;

int search(int code, const char *filename)
{
    // Binary search in file by code
    // returns a key
    // assuming that we actualy work with binary file

    std::pair<int, int> gg;
    std::vector<std::pair<int, int>> data;
    data.reserve(20);

    ifstream ifile;

    ifile.open(filename);

    if (!ifile)
    {
        return -1;
    }

    // here is weak moment
    while (!ifile.eof())
    {
        ifile >> gg.first >> gg.second;
        data.push_back(gg);
    }

    int beg = 0, end = data.size(), mid;

    while (end - beg > 1)
    {
        // std::cout << "ITERATION: " << beg << ' ' << end << '\n';
        mid = (beg + end) / 2;
        if (data[mid].second > code)
            end = mid;
        else if (data[mid].second < code)
        {
            beg = mid;
        }
        else
            return data[mid].first;
    }
    // std::cout << data.size() << std::endl;
    // std::cout << data[beg].second << std::endl;
    // std::cout << data[end].second << std::endl;

    if (data[beg].second == code)
        return data[beg].first;
    if (data[end].second == code)
        return data[end].first;

    return -1;
}

void change_index(int code, int new_index, const char *filename)
{
    int index;

    std::pair<int, int> index_code_pair;
    std::vector<std::pair<int, int>> data;
    data.reserve(20);

    ifstream ifile;
    std::ofstream ofile;

    ifile.open(filename);

    if (!ifile)
    {
        return;
    }

    // here is weak moment
    while (!ifile.eof())
    {

        ifile >> index_code_pair.first >> index_code_pair.second;

        data.push_back(index_code_pair);
    }

    ifile.close();

    int sz = data.size();

    ofile.open(filename);

    for (std::pair<int, int> el : data)
    {
        if (el.second != code)
            ofile << el.first << ' ' << el.second << '\n';
        else
            ofile << new_index << ' ' << code;
    }
}

void remove_index_record(int code, const char filename[] = "data/S.ind")
{
    int index;

    std::pair<int, int> index_code_pair;
    std::vector<std::pair<int, int>> data;
    data.reserve(20);

    ifstream ifile;
    std::ofstream ofile;

    ifile.open(filename);

    if (!ifile)
    {
        return;
    }

    // here is weak moment
    while (!ifile.eof())
    {

        ifile >> index_code_pair.first >> index_code_pair.second;

        data.push_back(index_code_pair);
    }

    ifile.close();

    int sz = data.size();

    ofile.open(filename);

    for (std::pair<int, int> el : data)
    {
        if (el.second != code)
            ofile << el.first << ' ' << el.second << '\n';
    }
}

void insert_index(int index, int code, const char *filename)
{
    std::pair<int, int> index_code_pair;
    std::vector<std::pair<int, int>> data;
    data.reserve(20);

    ifstream ifile;
    std::ofstream ofile;

    ifile.open(filename);

    // here is weak moment

    bool added = false;
    while (ifile.is_open() && !ifile.eof())
    {

        ifile >> index_code_pair.first >> index_code_pair.second;
        if (index_code_pair.second > code && !added)
        {
            data.push_back(std::make_pair(index, code));
            added = true;
        }

        data.push_back(index_code_pair);
    }

    if (!added)
    {
        if (data.size() > 1)
            data.pop_back(); // for some reason last record adds twice, so we need to pop it

        data.push_back(std::make_pair(index, code));
    }
    else
        data.pop_back();

    if (ifile.is_open())
        ifile.close();

    int sz = data.size();
    std::cout << data.size() << '\n';
    ofile.open(filename);

    for (std::pair<int, int> el : data)
    {
        ofile << el.first << ' ' << el.second << '\n';
    }
    ofile.close();
}

_delivery_dev *get_slave(int index, const char *slave_file)
{
    // std::cout << "Trying to get slave: " << index << '\n';
    FILE *file = fopen(slave_file, "rb");
    if (!file)
        return nullptr;

    // checking if file is empty
    fseek(file, 0L, SEEK_END);
    if (ftell(file) == 0)
        return nullptr;
    rewind(file);

    fseek(file, sizeof(_delivery_dev) * index, 0);
    _delivery_dev *dv = new _delivery_dev;
    fread(dv, sizeof(_delivery_dev), 1, file);

    fclose(file);

    return dv;
}

_delivery_dev *find_last_slave(int first_slave_index)
{
    // std::cout << "Running with " << first_slave_index << '\n';
    _delivery_dev *dv, *tmp;
    dv = tmp = nullptr;
    if (first_slave_index == -1)
        return nullptr;
    do
    {
        dv = get_slave(first_slave_index, SLAVE_FILE);

        if (!dv)
            return nullptr;

        // std::cout << "SLAVE SEARCHING: " << dv->index << '\n';
        first_slave_index = dv->next_ind;
        // std::cout << "NOW searching for: " << first_slave_index << '\n';

        if (tmp)
            delete tmp;
        tmp = dv;

    } while (dv && dv->next_ind != -1);

    return dv;
}

void print_slave(_delivery_dev *slave)
{
    using std::cout;
    cout << "Index in file: " << slave->index << '\n';
    cout << "  pcode: " << slave->master.code_p << "\n  dcode: " << slave->master.code_d << "\n  qt: " << slave->master.quantity << "\n  pr: " << slave->master.price << '\n';
    // cout << slave->prev_ind << ' ' << slave->next_ind << '\n';
}
void print_all_slaves()
{
    using std::cout;

    FILE *slave_file = fopen(SLAVE_FILE, "rb");

    _delivery_dev *slave = new _delivery_dev;
    while (!feof(slave_file))
    {
        fread(slave, sizeof(_delivery_dev), 1, slave_file);
        print_slave(slave);
    }
    delete slave;
    fclose(slave_file);
}

void print_master(_provider_dev *master)
{
    using std::cout;
    using std::endl;
    cout << "Position: " << master->position << endl;
    cout << "  code: " << master->master.code << "\n  surname: " << master->master.sur << "\n  city: " << master->master.city << endl;
}

void print_all_masters()
{
    FILE *master_file = fopen(PROVIDERS_DATA_FILE, "rb");

    _provider_dev *master = new _provider_dev;
    while (!feof(master_file))
    {
        fread(master, sizeof(_provider_dev), 1, master_file);
        print_master(master);
    }
    delete master;
    fclose(master_file);
}