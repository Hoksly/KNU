#include <vector>
#include "map.h"
#include <iostream>

using std::vector;
#ifndef ANT_H
#define ANT_H

template <class feromoneT, class distanceT>
class Ant
{
protected:
    vector<size_t> path;

public:
    virtual void run(size_t begin, const Map<distanceT, feromoneT> &) = 0;
    vector<size_t> getPath() { return path; };
};

#endif
