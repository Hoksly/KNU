#include "../maps/map.h"
#include "../colonies/colony.h"

#include <vector>
#ifndef CHOOSE_BEST_ROOT_H
#define CHOOSE_BEST_ROOT_H

template <class feromoneT, class distanceT>
class ChooseBestRootStrategy
{
public:
    virtual std::vector<size_t> chooseBestRoot(size_t begin, Map<distanceT, feromoneT> &map) = 0;
};

#endif