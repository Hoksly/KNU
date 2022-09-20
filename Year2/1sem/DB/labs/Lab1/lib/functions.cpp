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
    std::cout << "HERE11" << std::endl;
    ifstream ifile;

    ifile.open(filename);
    std::cout << "HERE12" << std::endl;

    if (!ifile)
    {
        return -1;
    }
    std::cout << "HERE13" << std::endl;

    // here is weak moment
    while (!ifile.eof())
    {
        ifile >> gg.first >> gg.second;
        data.push_back(gg);
    }
    std::cout << "HERE14" << std::endl;

    int beg = 0, end = data.size(), mid;

    while (end - beg > 1)
    {
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
    std::cout << data.size() << std::endl;
    std::cout << data[beg].second << std::endl;
    std::cout << data[end].second << std::endl;

    if (data[beg].second == code)
        return data[beg].first;
    if (data[end].second == code)
        return data[end].first;

    std::cout << "FUCk" << std::endl;

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
    FILE *file = fopen(slave_file, "rb");
    fseek(file, sizeof(_delivery_dev) * index, 0);

    _delivery_dev *dv = new _delivery_dev;
    fread(dv, sizeof(_delivery_dev), 1, file);

    fclose(file);

    return dv;
}

_delivery_dev *find_last_slave(int first_slave_index)
{
    _delivery_dev *dv, *tmp;
    dv = tmp = nullptr;

    do
    {
        dv = get_slave(first_slave_index, SLAVE_FILE);
        if (tmp)
        {
            delete tmp;
            tmp = dv;
        }
    } while (dv->next_ind != -1);

    return dv;
}