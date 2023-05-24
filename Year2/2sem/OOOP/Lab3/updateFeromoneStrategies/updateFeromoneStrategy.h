#include "../colony.h"
#ifndef UPDATE_FEROMONE_STRATEGY_H
#define UPDATE_FEROMONE_STRATEGY_H

template <class feromoneT, class distanceT>
class UpdateFeromoneStrategy
{
public:
    virtual void updateFeromone(Map<distanceT, feromoneT> &map, Colony<distanceT, feromoneT> &) = 0;
};
#endif
