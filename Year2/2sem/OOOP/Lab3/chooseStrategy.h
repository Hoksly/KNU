#include "map.h"
#ifndef CHOOSE_STRATEGY_H
#define CHOOSE_STRATEGY_H

template <class MapT>
class ChooseNextStrategy
{
public:
    std::size_t choose(const MapT &);
};

#endif