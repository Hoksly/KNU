#include "chooseBestRoot.h"
#include <vector>

#ifndef CHOOSE_BEST_FEROMONE_ROOT_H
#define CHOOSE_BEST_FEROMONE_ROOT_H

template <class feromoneT, class distanceT>
class ChooseBestFeromoneRoot : public ChooseBestRootStrategy<feromoneT, distanceT>
{
public:
    std::vector<size_t> chooseBestRoot(size_t begin, Map<distanceT, feromoneT> &map) override
    {
        std::vector<std::vector<feromoneT>> feromone = map.getFeromone();
        size_t n = feromone.size();

        std::vector<size_t> bestRoot;
        bestRoot.reserve(n + 1);

        feromoneT bestCurFeromone = 0;
        size_t nextNode = begin;

        bestRoot.push_back(begin);

        vector<bool> allowed(n, true);
        allowed[begin] = false;

        for (size_t i = 0; i < n; ++i)
        {
            bestCurFeromone = -1;

            for (size_t j = 0; j < n; ++j)
            {
                if (!allowed[j] || i == j)
                    continue;

                if (feromone[i][j] > bestCurFeromone)
                {
                    bestCurFeromone = feromone[i][j];
                    nextNode = j;
                }
            }
            bestRoot.push_back(nextNode);
            allowed[nextNode] = false;
        }

        bestRoot.push_back(bestRoot[0]);
        return bestRoot;
    }
};

#endif
