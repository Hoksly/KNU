#include <vector>
#include "../maps/map.h"
#include <iostream>
#include "../maps/map.h"

using std::vector;
#ifndef ANT_H
#define ANT_H

template <class feromoneT, class distanceT>
class Ant
{
protected:
    vector<size_t> path;
    feromoneT feromoneSpread;
    size_t begin;
    Map<feromoneT, distanceT> *mapRef;

public:
    virtual void run(size_t begin, Map<distanceT, feromoneT> &) = 0;
    virtual void run() = 0;

    vector<size_t> getPath() { return path; };
    feromoneT getFeromoneLeft() { return feromoneSpread; };
    void preRun(size_t begin, Map<distanceT, feromoneT> &map)
    {
        begin = begin;
        mapRef = &map;
    };
};

#endif
