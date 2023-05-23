#include "ant.h"
#include "chooseStrategy.h"
#include <iostream>

using std::size_t;
#ifndef BASIC_ANT_H
#define BASIC_ANT_H
template <class feromoneT, class distanceT>
class BasicAnt : public Ant<feromoneT, distanceT>
{

    vector<size_t> sth;

    std::unique_ptr<ChooseNextStrategy<feromoneT, distanceT>> chooseStrat;
    size_t choose(std::size_t curNode, const Map<distanceT, feromoneT> &);
    size_t curNode;
    vector<bool> available;

    size_t choose(const Map<distanceT, feromoneT> &map)
    {
        return chooseStrat->choose(curNode, map, available);
    }

public:
    BasicAnt(std::unique_ptr<ChooseNextStrategy<feromoneT, distanceT>> str) { chooseStrat = std::move(str); };

    void run(size_t begin, const Map<distanceT, feromoneT> &) override;
    vector<size_t> getPathBegin() { return this->path.begin(); };
    vector<size_t> getPathEnd() { return this->path.end(); };
};

template <class feromoneT, class distanceT>
void BasicAnt<feromoneT, distanceT>::run(size_t begin, const Map<distanceT, feromoneT> &map)
{
    std::cout << "BasicAnt run\n";
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
