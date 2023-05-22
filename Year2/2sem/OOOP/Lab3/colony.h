#include <cstdio>
#include <vector>
#include "ant.h"
#include "map.h"

#ifndef COLONY_H
#define COLONY_H
template <class distanceT, class feromoneT>
class Colony
{

    std::vector<Ant<distanceT>> population;

public:
    void run(const Map<distanceT, feromoneT> &);
    void run(const Map<distanceT, feromoneT> &, size_t iterations);

    Colony() = default;
    Colony(size_t size) { population.reserve(size); };
    Colony(const std::vector<Ant<distanceT>> &pop) { population = pop; };

    inline void addAnt(Ant<distanceT> &ant) { population.push_back(ant); };
    inline void clear() { population.clear(); };
};

#endif