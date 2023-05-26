#include "antAlgorithm.h"

#ifndef BASIC_ANT_ALGORITHM_H
#define BASIC_ANT_ALGORITHM_H

template <class feromoneT, class distanceT>
class BasicAntAlgorithm : public AntAlgorithm<feromoneT, distanceT>
{
protected:
    void runOnce(size_t begin);
    void runOnce(size_t begin, typename mapCoroutine<distanceT>::push_type &sink);
    size_t beginNode = 0;

public:
    BasicAntAlgorithm(std::shared_ptr<Map<distanceT, feromoneT>> &map,
                      std::shared_ptr<Colony<feromoneT, distanceT>> &colony,
                      std::shared_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> &updateStrategy,
                      std::shared_ptr<ChooseBestRootStrategy<feromoneT, distanceT>> &chooseRootStrategy)
        : AntAlgorithm<feromoneT, distanceT>(map, colony, updateStrategy, chooseRootStrategy) {}

    void run(size_t begin, size_t iterations) override;
    void run(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink) override;
    std::vector<size_t> getBestPath() override;
    distanceT calcBestPathLength(std::vector<size_t>) override;
    distanceT calcBestPathLength() override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class feromoneT, class distanceT>
void BasicAntAlgorithm<feromoneT, distanceT>::runOnce(size_t begin)
{
    for (auto &ant : *(this->colony))
    {
        ant->run(begin, *(this->map));
    }
    this->updateStrategy->updateFeromone(*(this->map), *(this->colony));
}

template <class feromoneT, class distanceT>
void BasicAntAlgorithm<feromoneT, distanceT>::run(size_t begin, size_t iterations)
{
    beginNode = begin;

    for (size_t i = 0; i < iterations; ++i)
    {
        runOnce(begin);
    }
}
template <class feromoneT, class distanceT>
void BasicAntAlgorithm<feromoneT, distanceT>::runOnce(size_t begin, typename mapCoroutine<distanceT>::push_type &sink)
{
    for (auto &ant : *(this->colony))
    {
        ant->run(begin, *(this->map));
    }

    this->updateStrategy->updateFeromone(*(this->map), *(this->colony));
    sink(this->map->getFeromone());
}

template <class feromoneT, class distanceT>
void BasicAntAlgorithm<feromoneT, distanceT>::run(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink)
{
    beginNode = begin;

    for (size_t i = 0; i < iterations; ++i)
    {
        runOnce(begin, sink);
    }
}

template <class feromoneT, class distanceT>
std::vector<size_t> BasicAntAlgorithm<feromoneT, distanceT>::getBestPath()
{
    return this->chooseRootStrategy->chooseBestRoot(beginNode, *(this->map));
}

template <class feromoneT, class distanceT>
distanceT BasicAntAlgorithm<feromoneT, distanceT>::calcBestPathLength(std::vector<size_t> path)
{
    distanceT length = 0;
    size_t n = path.size() - 1;
    for (size_t i = 0; i < n; ++i)
    {
        length += this->map->getDistance(path[i])[path[i + 1]];
    }
    return length;
}

template <class feromoneT, class distanceT>
distanceT BasicAntAlgorithm<feromoneT, distanceT>::calcBestPathLength()
{
    return calcBestPathLength(getBestPath());
}

#endif