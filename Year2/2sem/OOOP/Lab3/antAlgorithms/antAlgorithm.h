#include "../maps/map.h"
#include "../colonies/colony.h"
#include "../chooseNextNodeStrategies/chooseStrategy.h"
#include "../updateFeromoneStrategies/updateFeromoneStrategy.h"
#include "../ants/ant.h"
#include "../chooseBestRootStrategies/chooseBestRoot.h"

#include <vector>
#include <boost/coroutine2/coroutine.hpp>
#include <iostream>
#include <memory>

#ifndef ANT_ALGORITHM_H
#define ANT_ALGORITHM_H

template <class distanceT>
using mapCoroutine = typename boost::coroutines2::coroutine<std::vector<std::vector<distanceT>>>;

template <class feromoneT, class distanceT>
class AntAlgorithm
{
protected:
    std::unique_ptr<Map<distanceT, feromoneT>> map;
    std::unique_ptr<Colony<feromoneT, distanceT>> colony;
    std::unique_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> updateStrategy;
    std::unique_ptr<ChooseBestRootStrategy<feromoneT, distanceT>> chooseRootStrategy;

public:
    AntAlgorithm(std::unique_ptr<Map<distanceT, feromoneT>> &map,
                 std::unique_ptr<Colony<feromoneT, distanceT>> &colony,
                 std::unique_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> &updateStrategy,
                 std::unique_ptr<ChooseBestRootStrategy<feromoneT, distanceT>> &chooseRootStrategy)
    {
        this->map = std::move(map);
        this->colony = std::move(colony);
        this->updateStrategy = std::move(updateStrategy);
        this->chooseRootStrategy = std::move(chooseRootStrategy);
    }

    virtual void run(size_t begin, size_t iterations) = 0;
    virtual void run(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink) = 0;

    virtual std::vector<size_t> getBestPath() = 0;

    virtual distanceT calcBestPathLength(std::vector<size_t>) = 0;
    virtual distanceT calcBestPathLength() = 0;
};

#endif