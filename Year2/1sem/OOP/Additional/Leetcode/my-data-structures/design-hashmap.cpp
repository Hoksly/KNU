#include <bits/stdc++.h>

using namespace std;

class MyHashMap
{
private:
    int CAPACITY = 10000;
    vector<vector<pair<int, int>>> table;

    size_t hash(int key)
    {
        return key % CAPACITY;
    }

    vector<pair<int, int>>::iterator search(int key)
    {
        size_t index = hash(key);
        vector<pair<int, int>>::iterator itr = table[index].begin();

        while (itr != table[index].end())
        {
            if (itr->first == key)
                return itr;
            itr++;
        }
        return itr;
    }

public:
    MyHashMap()
    {
        table.resize(CAPACITY, vector<pair<int, int>>());
    }

    void put(int key, int value)
    {

        size_t index = hash(key);
        remove(key);
        table[index].push_back({key, value});
    }

    int get(int key)
    {

        size_t index = hash(key);
        vector<pair<int, int>>::iterator itr = search(key);
        if (itr == table[index].end())
            return -1;

        return itr->second;
    }

    void remove(int key)
    {

        size_t index = hash(key);
        vector<pair<int, int>>::iterator itr = search(key);

        if (itr != table[index].end())
            table[index].erase(itr);
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */