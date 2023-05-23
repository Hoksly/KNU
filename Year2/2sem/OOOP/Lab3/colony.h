#include <cstdio>
#include <vector>
#include "ant.h"
#include "map.h"

#ifndef COLONY_H
#define COLONY_H
template <class distanceT, class feromoneT>
class Colony
{

    std::vector<Ant<distanceT, feromoneT>> population;

public:
    void run(const Map<distanceT, feromoneT> &);
    void run(const Map<distanceT, feromoneT> &, size_t iterations);

    Colony() = default;
    Colony(size_t size) { population.reserve(size); };
    Colony(const std::vector<Ant<distanceT, feromoneT>> &pop) { population = pop; };

    inline void addAnt(Ant<distanceT, feromoneT> &ant) { population.push_back(ant); };
    inline void clear() { population.clear(); };
    inline size_t size() { return population.size(); }
};

#endif