#include "map.h"
#include "colony.h"
#include "chooseStrategy.h"
#include "updateFeromoneStrategy.h"
#include "ant.h"
#include <vector>
#include <boost/coroutine2/coroutine.hpp>
#include <iostream>
#include <memory>

template <class distanceT>
using mapCoroutine = typename boost::coroutines2::coroutine<std::vector<std::vector<distanceT>>>;

template <class feromoneT, class distanceT>
class AntAlgorithm
{
protected:
    std::unique_ptr<Map<distanceT, feromoneT>> map;
    std::unique_ptr<Colony<feromoneT, distanceT>> colony;
    std::unique_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> updateStrategy;

public:
    AntAlgorithm(std::unique_ptr<Map<distanceT, feromoneT>> &map,
                 std::unique_ptr<Colony<feromoneT, distanceT>> &colony,
                 std::unique_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> &updateStrategy)
    {
        this->map = std::move(map);
        this->colony = std::move(colony);
        this->updateStrategy = std::move(updateStrategy);
    }

    virtual void run(size_t begin, size_t iterations) = 0;
    virtual void run(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink) = 0;
};

template <class feromoneT, class distanceT>
class BasicAntAlgorithm : public AntAlgorithm<feromoneT, distanceT>
{
protected:
    void runOnce(size_t begin);
    void runOnce(size_t begin, typename mapCoroutine<distanceT>::push_type &sink);

public:
    BasicAntAlgorithm(std::unique_ptr<Map<distanceT, feromoneT>> &map,
                      std::unique_ptr<Colony<feromoneT, distanceT>> &colony,
                      std::unique_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> &updateStrategy)
        : AntAlgorithm<feromoneT, distanceT>(map, colony, updateStrategy) {}

    void run(size_t begin, size_t iterations) override;
    void run(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink) override;
};

template <class feromoneT, class distanceT>
void BasicAntAlgorithm<feromoneT, distanceT>::runOnce(size_t begin)
{
    for (auto &ant : *(this->colony))
    {
        ant->run(begin, *(this->map));
    }
    this->updateStrategy->updateFeromone(*(this->map));
}

template <class feromoneT, class distanceT>
void BasicAntAlgorithm<feromoneT, distanceT>::run(size_t begin, size_t iterations)
{
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

    this->updateStrategy->updateFeromone(*(this->map));
    sink(this->map->getFeromone());
}

template <class feromoneT, class distanceT>
void BasicAntAlgorithm<feromoneT, distanceT>::run(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink)
{
    for (size_t i = 0; i < iterations; ++i)
    {
        runOnce(begin, sink);
    }
}
