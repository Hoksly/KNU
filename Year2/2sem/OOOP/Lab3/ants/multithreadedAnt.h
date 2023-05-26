#include "ant.h"
#include "../chooseNextNodeStrategies/chooseStrategy.h"
#include <iostream>

using std::size_t;
#ifndef MULTITHREADED_ANT_H
#define MULTITHREADED_ANT_H
template <class feromoneT, class distanceT>
class MultithreadedAnt : public Ant<feromoneT, distanceT>
{

    vector<size_t> sth;

    std::shared_ptr<ChooseNextStrategy<feromoneT, distanceT>> chooseStrat;
    size_t choose(std::size_t curNode, Map<distanceT, feromoneT> &);
    size_t curNode;
    vector<bool> available;

    size_t begin;
    Map<distanceT, feromoneT> &mapRef;
    size_t choose(Map<distanceT, feromoneT> &map)
    {
        return chooseStrat->choose(curNode, map, available);
    }

public:
    MultithreadedAnt(std::shared_ptr<ChooseNextStrategy<feromoneT, distanceT>> str)
    {
        chooseStrat = std::move(str);
        this->feromoneSpread = 1;
    };

    MultithreadedAnt(std::shared_ptr<ChooseNextStrategy<feromoneT, distanceT>> str, feromoneT feromoneSpread)
    {
        chooseStrat = std::move(str);
        this->feromoneSpread = feromoneSpread;
    };

    void run(size_t begin, Map<distanceT, feromoneT> &) override;
    void run() override { throw std::runtime_error("Not implemented for this ant"); };

    vector<size_t> getPathBegin()
    {
        return this->path.begin();
    };
    vector<size_t> getPathEnd()
    {
        return this->path.end();
    };
};

template <class feromoneT, class distanceT>
void MultithreadedAnt<feromoneT, distanceT>::run(size_t begin, Map<distanceT, feromoneT> &map)
{
    this->path.resize(map.size() + 1);
    available.resize(map.size());

    std::fill(available.begin(), available.end(), true);

    curNode = begin;
    available[begin] = false;

    size_t n = map.size();
    for (size_t i = 1; i < n; ++i)
    {

        size_t nextNode = this->choose(map);
        available[nextNode] = false;

        this->path[i] = nextNode;
    }
    this->path[map.size()] = this->path[0] = begin;
}

#endif
