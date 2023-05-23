#include "map.h"
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>

using std::vector;

#ifndef CHOOSE_STRATEGY_H
#define CHOOSE_STRATEGY_H

template <class feromoneT, class distanceT>
class ChooseNextStrategy
{
public:
    std::size_t choose(std::size_t curNode, const Map<distanceT, feromoneT> &, const vector<bool> &);
};

template <class feromoneT, class distanceT>
class BasicChooseStrategy : public ChooseNextStrategy<distanceT, feromoneT>
{
    feromoneT feromoneImpact = 1;
    distanceT distanceImpact = 1;
    vector<distanceT> imapctCombined;

    distanceT getRandomValue()
    {
        std::random_device rd;
        std::mt19937 generator(rd());

        // Define a uniform distribution between 0 and 1
        std::uniform_real_distribution<distanceT> distribution(0.0, 1.0);

        // Generate a random value between 0 and 1
        return distribution(generator);
    }

    std::size_t chooseFromNormalized()
    {
        distanceT val = getRandomValue();

        distanceT curSum = 0;

        size_t n = imapctCombined.size();

        for (size_t i = 0; i < n; ++i)
        {
            curSum += imapctCombined[i];
            if (val < curSum)
                return i;
        }
        return n - 1;
    }

public:
    BasicChooseStrategy() = default;
    BasicChooseStrategy(feromoneT a, distanceT b) : feromoneImpact(a), distanceImpact(b) {}

    std::size_t
    choose(std::size_t curNode, const Map<distanceT, feromoneT> &map, const vector<bool> &availiable)
    {
        vector<feromoneT> feromone = map.feromone(curNode);
        vector<distanceT> distance = map.distance(curNode);

        imapctCombined.reserve(feromone.size() / 2);

        size_t n = feromone.size();
        for (size_t i = 0; i < n; ++i)
        {
            if (!availiable[i])
                continue;

            imapctCombined.push_back(
                pow(feromone[i], feromoneImpact) *
                pow(distance[i], distanceImpact));
        }

        distanceT sum = (std::accumulate(imapctCombined.begin(), imapctCombined.end(), 0));

        std::for_each(imapctCombined.begin(), imapctCombined.end(), [sum](distanceT &c)
                      { c /= sum; });

        return chooseFromNormalized;
    }
};

#endif