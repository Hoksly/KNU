
#include "../ants/multithreadedAnt.h"

#include "antAlgorithm.h"
#include <unistd.h>
#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>

template <class feromoneT, class distanceT>
class MultyThreadedAntAlgorithm : public AntAlgorithm<feromoneT, distanceT>
{
protected:
    void runOnce(size_t begin);
    void runOnce(size_t begin, typename mapCoroutine<distanceT>::push_type &sink);
    size_t beginNode = 0;
    size_t threadsCount = 0;

public:
    MultyThreadedAntAlgorithm(std::shared_ptr<Map<distanceT, feromoneT>> &map,
                              std::shared_ptr<Colony<feromoneT, distanceT>> &colony,
                              std::shared_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> &updateStrategy,
                              std::shared_ptr<ChooseBestRootStrategy<feromoneT, distanceT>> &chooseRootStrategy, size_t threadsCount = 0)
        : AntAlgorithm<feromoneT, distanceT>(map, colony, updateStrategy, chooseRootStrategy), threadsCount(threadsCount) {}

    void run(size_t begin, size_t iterations) override;
    void run(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink) override;

    double runGetTime(size_t begin, size_t iterations) override;
    double runGetTime(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink) override;

    std::vector<size_t> getBestPath() override;
    distanceT calcBestPathLength(std::vector<size_t>) override;
    distanceT calcBestPathLength() override;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class feromoneT, class distanceT>
void MultyThreadedAntAlgorithm<feromoneT, distanceT>::runOnce(size_t begin)
{

    boost::asio::thread_pool pool(threadsCount ?: sysconf(_SC_NPROCESSORS_CONF));
    auto mp = this->map;
    for (auto &ant : *(this->colony))
    {

        boost::asio::post(pool, [ant, begin, mp]()
                          { ant->run(begin, *(mp)); });
    }

    pool.join();

    this->updateStrategy->updateFeromone(*(this->map), *(this->colony));
}

template <class feromoneT, class distanceT>
void MultyThreadedAntAlgorithm<feromoneT, distanceT>::run(size_t begin, size_t iterations)
{
    beginNode = begin;

    for (size_t i = 0; i < iterations; ++i)
    {
        runOnce(begin);
    }
}
template <class feromoneT, class distanceT>
void MultyThreadedAntAlgorithm<feromoneT, distanceT>::runOnce(size_t begin, typename mapCoroutine<distanceT>::push_type &sink)
{
    boost::asio::thread_pool pool(threadsCount ?: sysconf(_SC_NPROCESSORS_CONF));
    auto mp = this->map;

      for (auto &ant : *(this->colony))
    {

        boost::asio::post(pool, [ant, begin, mp]()
                          { ant->run(begin, *(mp)); });
    }
    pool.join();

    this->updateStrategy->updateFeromone(*(this->map), *(this->colony));
    sink(this->map->getFeromone());
}

template <class feromoneT, class distanceT>
void MultyThreadedAntAlgorithm<feromoneT, distanceT>::run(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink)
{
    beginNode = begin;

    for (size_t i = 0; i < iterations; ++i)
    {
        std::cout << i << std::endl;
        runOnce(begin, sink);
    }
}

template <class feromoneT, class distanceT>
std::vector<size_t> MultyThreadedAntAlgorithm<feromoneT, distanceT>::getBestPath()
{
    return this->chooseRootStrategy->chooseBestRoot(beginNode, *(this->map));
}

template <class feromoneT, class distanceT>
distanceT MultyThreadedAntAlgorithm<feromoneT, distanceT>::calcBestPathLength(std::vector<size_t> path)
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
distanceT MultyThreadedAntAlgorithm<feromoneT, distanceT>::calcBestPathLength()
{
    return calcBestPathLength(getBestPath());
}

template <class feromoneT, class distanceT>
double MultyThreadedAntAlgorithm<feromoneT, distanceT>::runGetTime(size_t begin, size_t iterations) {
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    this->run(begin, iterations);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Print the execution time
    return static_cast<double>(duration.count()) / 1000.0;
}


template <class feromoneT, class distanceT>
double MultyThreadedAntAlgorithm<feromoneT, distanceT>::runGetTime(size_t begin, size_t iterations, typename mapCoroutine<distanceT>::push_type &sink) {
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    this->run(begin, iterations, sink);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Print the execution time
    return static_cast<double>(duration.count()) / 1000.0;
}
