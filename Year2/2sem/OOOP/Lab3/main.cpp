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

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        std::cout << "Usage: " << argv[0] << " <size of map>, <size of colony> <iterations>" << std::endl;
        return 1;
    }

    size_t mapSize = std::stoi(argv[1]);
    size_t colonySize = std::stoi(argv[2]);
    size_t iterations = std::stoi(argv[3]);

    AntAlgorithmFactory<double, double> factory;
    std::shared_ptr<AntAlgorithm<double, double>> algMultPtr = factory.createAlgorithm("multithreaded", colonySize, 0.6);
    std::shared_ptr<AntAlgorithm<double, double>> algBasicPtr = factory.createAlgorithm("basic", colonySize, 0.6);

    std::vector<std::pair<double, double>> points = getRandomPoints(mapSize);

    algMultPtr->getMap()->fromCoordinates(points, 1.0);

    auto start = std::chrono::high_resolution_clock::now();
    algMultPtr->run(0, iterations);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << algMultPtr->calcBestPathLength() << " ";
    std::cout << static_cast<double>(duration) / 1000.0 << std::endl;

    algBasicPtr->getMap()->fromCoordinates(points, 1.0);
    start = std::chrono::high_resolution_clock::now();

    algBasicPtr->run(0, iterations);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << algBasicPtr->calcBestPathLength() << " ";
    std::cout << static_cast<double>(duration) / 1000.0 << std::endl;

    return 0;
}

/*
Write a GUI on Qt for this algorithm assuming that backend is already written.  It must consist of:
1) Canvas with points, which are nodes of the graph. User can add new points by clicking on the canvas.
2) Button "Run" which starts the algorithm.
3) Entry for the number of iterations.
4) Entry for the number of ants.

Also canvas must support drawing lines that represent quantity of feromone on the edge.



*/