#include <cstdio>
#include <vector>
#include <memory>

#include "ant.h"
#include "map.h"
#ifndef COLONY_H
#define COLONY_H
template <class distanceT, class feromoneT>
class Colony
{

    std::vector<std::unique_ptr<Ant<distanceT, feromoneT>>> population;

public:
    void run(const Map<distanceT, feromoneT> &);
    void run(const Map<distanceT, feromoneT> &, size_t iterations);

    Colony() = default;
    Colony(size_t size) { population.reserve(size); };
    Colony(const std::vector<std::unique_ptr<Ant<distanceT, feromoneT>>> &pop) { population = pop; };

    inline std::unique_ptr<Ant<distanceT, feromoneT>> &operator[](size_t i) { return population[i]; };
    inline const std::unique_ptr<Ant<distanceT, feromoneT>> &operator[](size_t i) const { return population[i]; };

    inline typename std::vector<std::unique_ptr<Ant<distanceT, feromoneT>>>::iterator begin() { return population.begin(); };

    inline typename std::vector<std::unique_ptr<Ant<distanceT, feromoneT>>>::iterator end() { return population.end(); };

    inline void addAnt(std::unique_ptr<Ant<distanceT, feromoneT>> &&antPtr) { population.push_back(std::move(antPtr)); };
    inline void clear() { population.clear(); };
    inline size_t size() { return population.size(); }
};

#endif