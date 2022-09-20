#include "lib/get.hpp"
#include "lib/insert.hpp"
#include <iostream>
#define MASTER_INDEX_FILE "data/S.ind"
#include <fstream>
#include <vector>
#define MASTER_DATA_FILE "data/S.fl"

using namespace std;

int main()
{
    provider *pr;
    ifstream file;

    file.open("SampleData/Providers.txt");
    vector<pair<int, pair<string, string>>> V;

    pair<int, pair<string, string>> p;
    while (!file.eof())
    {
        file >> p.first >> p.second.first >> p.second.second;
        cout << p.first << p.second.first << p.second.second << endl;
        V.push_back(p);
    }
    V.pop_back();
    for (pair<int, pair<string, string>> a : V)
    {
        insert_provider(a.first, a.second.first.c_str(), a.second.second.c_str());
    }

    return 0;
}