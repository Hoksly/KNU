#include "antAlgorithms/basicAntAlgotiyhm.h"
#include "colonies/colony.h"
#include "maps/map.h"
#include "ants/basicAnt.h"
#include "chooseNextNodeStrategies/chooseStrategy.h"
#include "updateFeromoneStrategies/basicFeromoneDecayStrategy.h"
#include "chooseBestRootStrategies/chooseBestFeromoneRoot.h"
#include "antAlgorithms/antAlgorithmFactory.h"
#include <iostream>
#include <memory>
#include <chrono>

template <class distanceT>
using mapCoroutine = typename boost::coroutines2::coroutine<std::vector<std::vector<distanceT>>>;

template <class distanceT>
void printMap(std::vector<std::vector<distanceT>> &map)
{
    for (auto &row : map)
    {
        for (auto &el : row)
        {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::pair<double, double>> getRandomPoints(size_t n)
{
    double randDist;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    std::vector<std::pair<double, double>> points(n);

    for (size_t i = 0; i < n; ++i)
    {
        points[i].first = distribution(generator);
        points[i].second = distribution(generator);
    }
    return points;
}

void testCol()
{
    size_t iterations = 100;
    AntAlgorithmFactory<double, double> factory;

    for (size_t colonySize = 1; colonySize < 2000; colonySize += 20)
    {
        std::cout << colonySize << std::endl;

        std::shared_ptr<AntAlgorithm<double, double>> algMultPtr = factory.createAlgorithm("multithreaded", colonySize, 0.6);
        std::shared_ptr<AntAlgorithm<double, double>> algBasicPtr = factory.createAlgorithm("basic", colonySize, 0.6);

        algMultPtr->getMap()->fromFile("input.txt", 1.0);

        auto start = std::chrono::high_resolution_clock::now();
        algMultPtr->run(0, iterations);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << algMultPtr->calcBestPathLength() << " ";
        std::cout << static_cast<double>(duration) / 1000.0 << std::endl;

        algBasicPtr->getMap()->fromFile("input.txt", 1.0);
        start = std::chrono::high_resolution_clock::now();

        algBasicPtr->run(0, iterations);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << algBasicPtr->calcBestPathLength() << " ";
        std::cout << static_cast<double>(duration) / 1000.0 << std::endl;
    }
}

void testMap()
{
}

void testIteration()
{

    AntAlgorithmFactory<double, double> factory;
    std::shared_ptr<AntAlgorithm<double, double>> algMultPtr = factory.createAlgorithm("multithreaded", 100, 0.6);

    algMultPtr->getMap()->fromFile("input.txt", 1.0);

    for (size_t i = 0; i < 10000; i += 20)
    {
        auto start = std::chrono::high_resolution_clock::now();

        algMultPtr->run(0, i);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << i << " ";
        std::cout << algMultPtr->calcBestPathLength() << " ";

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << static_cast<double>(duration) / 1000.0 << std::endl;
    }
}

int main(int argc, char *argv[])
{

    size_t mapSize = 40;
    // size_t colonySize = std::stoi(argv[2]);
    size_t iterations = 100;

    AntAlgorithmFactory<double, double> factory;

    freopen("output1.txt", "w", stdout);
    testIteration();

    return 0;
}

