#include <vector>

using std::vector;
#ifndef ANT_H
#define ANT_H

template <class MapT>
class Ant
{

    vector<size_t> path;

public:
    Ant() = default;
    virtual void run(const MapT &) = 0;
};

#endif
