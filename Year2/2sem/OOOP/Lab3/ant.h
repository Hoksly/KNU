#include <vector>
#include "map.h"
using std::vector;
#ifndef ANT_H
#define ANT_H

template <class feromoneT, class distanceT>
class Ant
{

    vector<size_t> path;

public:
    void run(size_t begin, const Map<distanceT, feromoneT> &);
};

#endif
