#include "lib/get.hpp"
#include "lib/insert.hpp"
#include <iostream>
#define MASTER_INDEX_FILE "data/S.ind"
#include <fstream>
#include <vector>
#define MASTER_DATA_FILE "data/S.fl"

using namespace std;

struct tmp
{
    int i, mas;
    string s1, s2, s3;
};

int main()
{
    provider *pr;
    ifstream file;

    file.open("SampleData/Details.txt");
    vector<tmp> V;

    tmp tt;
    while (!file.eof())
    {

        file >> tt.i >> tt.s1 >> tt.mas >> tt.s2 >> tt.s3;

        V.push_back(tt);
    }
    V.pop_back();
    for (tmp a : V)
    {
        insert_detail(a.i, a.s1.c_str(), a.mas, a.s2.c_str(), a.s3.c_str());
    }

    return 0;
}