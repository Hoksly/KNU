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
    virtual std::size_t choose(std::size_t curNode, Map<distanceT, feromoneT> &, const vector<bool> &) = 0;
};

template <class feromoneT, class distanceT>
class BasicChooseStrategy : public ChooseNextStrategy<distanceT, feromoneT>
{
    feromoneT feromoneImpact = 1;
    distanceT distanceImpact = 1;

    vector<std::pair<distanceT, size_t>> imapctCombined;

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
            curSum += imapctCombined[i].first;
            if (val < curSum)
                return imapctCombined[i].second;
        }
        return imapctCombined[n - 1].second;
    }

public:
    BasicChooseStrategy() = default;
    BasicChooseStrategy(feromoneT a, distanceT b) : feromoneImpact(a), distanceImpact(b) {}

    std::size_t
    choose(std::size_t curNode, Map<distanceT, feromoneT> &map, const vector<bool> &availiable) override
    {
        vector<feromoneT> feromone = map.getFeromone(curNode);
        vector<distanceT> distance = map.getDistance(curNode);
        imapctCombined.clear();

        size_t n = feromone.size();
        for (size_t i = 0; i < n; ++i)
        {
            if (!availiable[i])
                continue;

            imapctCombined.push_back(std::make_pair(pow(feromone[i], feromoneImpact) *
                                                        pow(distance[i], distanceImpact),
                                                    i));
        }

        distanceT sum = 0;
        for (auto &c : imapctCombined)
            sum += c.first;

        std::for_each(imapctCombined.begin(), imapctCombined.end(), [sum](std::pair<distanceT, size_t> &c)
                      { c.first /= sum; });

        return chooseFromNormalized();
    }
};

template <class feromoneT, class distanceT>
class ChooseMaxFeromoneStratgey : public ChooseNextStrategy<distanceT, feromoneT>
{
    std::size_t choose(std::size_t curNode, Map<distanceT, feromoneT> &map, const vector<bool> &availiable) override
    {
        vector<feromoneT> feromone = map.getFeromone(curNode);
        vector<distanceT> distance = map.getDistance(curNode);

        size_t n = feromone.size();
        feromoneT maxFeromone = 0;
        size_t maxFeromoneIndex = 0;

        for (size_t i = 0; i < n; ++i)
        {
            if (!availiable[i])
                continue;

            if (feromone[i] > maxFeromone)
            {
                maxFeromone = feromone[i];
                maxFeromoneIndex = i;
            }
        }

        return maxFeromoneIndex;
    }
};

template <class feromoneT, class distanceT>
class ChooseStrategyFactory
{
public:
    static std::unique_ptr<ChooseNextStrategy<feromoneT, distanceT>>

    createStrategy(std::string name, feromoneT a = 1, distanceT b = 1)
    {
        if (name == "basic")
        {
            std::unique_ptr<BasicChooseStrategy<feromoneT, distanceT>> basicStrat = std::make_unique<BasicChooseStrategy<feromoneT, distanceT>>(a, b);
            std::unique_ptr<ChooseNextStrategy<feromoneT, distanceT>> str = std::move(basicStrat);
            return str;
        }
        else if (name == "feromone")
        {

            std::unique_ptr<ChooseMaxFeromoneStratgey<feromoneT, distanceT>> basicStrat = std::make_unique<ChooseMaxFeromoneStratgey<feromoneT, distanceT>>();
            std::unique_ptr<ChooseNextStrategy<feromoneT, distanceT>> str = std::move(basicStrat);
            return str;
        }

        else
            return nullptr;
    }
};

#endif