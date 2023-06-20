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
    std::shared_ptr<Map<distanceT, feromoneT>> map;
    std::shared_ptr<Colony<feromoneT, distanceT>> colony;
    std::shared_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> updateStrategy;
    std::shared_ptr<ChooseBestRootStrategy<feromoneT, distanceT>> chooseRootStrategy;

public:
    /**
     * Constructor for the AntAlgorithm class.
     *
     * @param map A shared pointer to the Map object.
     * @param colony A shared pointer to the Colony object.
     * @param updateStrategy A shared pointer to the UpdateFeromoneStrategy object.
     * @param chooseRootStrategy A shared pointer to the ChooseBestRootStrategy object.
     */

    AntAlgorithm(std::shared_ptr<Map<distanceT, feromoneT>> &map,
                 std::shared_ptr<Colony<feromoneT, distanceT>> &colony,
                 std::shared_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> &updateStrategy,
                 std::shared_ptr<ChooseBestRootStrategy<feromoneT, distanceT>> &chooseRootStrategy)
    {
        this->map = std::move(map);
        this->colony = std::move(colony);
        this->updateStrategy = std::move(updateStrategy);
        this->chooseRootStrategy = std::move(chooseRootStrategy);
    }
    /**
     * Get the Map object.
     *
     * @return A reference to the Map object.
     */
    inline std::shared_ptr<Map<distanceT, feromoneT>> &getMap() { return map; }
    /**
     * Get the Colony object.
     *
     * @return A reference to the Colony object.
     */
    inline std::shared_ptr<Colony<feromoneT, distanceT>> &getColony() { return colony; }
    /**
     * Get the UpdateFeromoneStrategy object.
     *
     * @return A reference to the UpdateFeromoneStrategy object.
     */
    inline std::shared_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> &getUpdateStrategy() { return updateStrategy; }
    /**
     * Get the ChooseBestRootStrategy object.
     *
     * @return A reference to the ChooseBestRootStrategy object.
     */
    inline std::shared_ptr<ChooseBestRootStrategy<feromoneT, distanceT>> &getChooseRootStrategy() { return chooseRootStrategy; }

    /**
     * Run the ant algorithm for a specified number of iterations, starting from a given index.
     *
     * @param begin The starting index.
     * @param iterations The number of iterations.
     */
    virtual void run(size_t begin, size_t iterations) = 0;
    /**
     * Run the ant algorithm for a specified number of iterations, starting from a given index, and provide output using a coroutine sink.
     *
     * @param begin The starting index.
     * @param iterations The number of iterations.
     * @param sink The coroutine sink for output.
     */
    virtual void run(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink) = 0;
    /**
     * Run the ant algorithm for a specified number of iterations, starting from a given index, and return the execution time.
     *
     * @param begin The starting index.
     * @param iterations The number of iterations.
     * @return The execution time in seconds.
     */
    virtual double runGetTime(size_t begin, size_t iterations) = 0;
    /*
     * Run the ant algorithm for a specified number of iterations, starting from a given index, provide output using a coroutine sink, and return the execution time.
     *
     * @param begin The starting index.
     * @param iterations The number of iterations.
     * @param sink The coroutine sink for output.
     * @return The execution time in seconds.
     *
     */
    virtual double runGetTime(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink) = 0;

    /*
     * Get the best path found by the algorithm.
     *
     * @return A vector of indices of the best path.
     *
     */
    virtual std::vector<size_t> getBestPath() = 0;

    /*
     * Get the length of the best path found by the algorithm.
     *
     * @return The length of the best path.
     *
     */

    virtual distanceT calcBestPathLength(std::vector<size_t>) = 0;
    /*
     * Get the length of the best path found by the algorithm.
     *
     * @return The length of the best path.
     */
    virtual distanceT calcBestPathLength() = 0;
};

#endif