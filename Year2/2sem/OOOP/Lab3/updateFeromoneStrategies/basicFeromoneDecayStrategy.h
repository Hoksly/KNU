#include "updateFeromoneStrategy.h"

#ifndef BASIC_FEROMONE_DECAY_STRATEGY_H
#define BASIC_FEROMONE_DECAY_STRATEGY_H

template <class feromoneT, class distanceT>
class BasicFeromoneDecay : public UpdateFeromoneStrategy<feromoneT, distanceT>
{
private:
    feromoneT decayCoeff;

public:
    BasicFeromoneDecay() = default;
    BasicFeromoneDecay(feromoneT decayCoeff) : decayCoeff(decayCoeff) {}

    void updateFeromone(Map<distanceT, feromoneT> &map, Colony<distanceT, feromoneT> &col) override
    {

        std::vector<std::unique_ptr<Ant<distanceT, feromoneT>>> &population = col.getPopulation();
        size_t n = population.size();
        for (size_t i = 0; i < n; ++i)
        {
            vector<size_t> path = population[i]->getPath();
            feromoneT feromoneLeft = population[i]->getFeromoneLeft();
            size_t nPath = path.size();
            for (size_t j = 1; j < nPath; ++j)
            {
                map.getFeromone()[path[j]][path[j - 1]] += feromoneLeft;
                map.getFeromone()[path[j - 1]][path[j]] += feromoneLeft;
            }
        }

        vector<vector<feromoneT>> feromone = map.getFeromone();

        for (size_t i = 0; i < feromone.size(); ++i)
        {
            for (size_t j = 0; j < feromone.size(); ++j)
            {
                map.getFeromone()[i][j] *= decayCoeff;
            }
        }
    }
};
#endif