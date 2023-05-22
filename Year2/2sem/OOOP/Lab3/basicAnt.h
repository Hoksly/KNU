#include "ant.h"
#include <iostream>

using std::size_t;
#ifndef BASIC_ANT_H
#define BASIC_ANT_H
template <class MapT>
class BasicAnt : Ant<MapT>
{
    vector<size_t> sth;

public:
    size_t choose(const MapT &);
    size_t curNode;

public:
    void run(size_t begin, const MapT &);
    vector<size_t> getPath() { return this->path; };
};

template <class MapT>
void BasicAnt<MapT>::run(size_t begin, const MapT &map)
{
    this->path.resize(map.size() + 1);
    curNode = begin;

    size_t n = map.size();
    for (size_t i = i; i < n; ++i)
    {
        size_t nextNode = this->choose(map);
        this->path[i] = nextNode;
    }
}

#endif
