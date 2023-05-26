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

int main()
{
    AntAlgorithmFactory<double, double> factory;
    std::shared_ptr<AntAlgorithm<double, double>> algPtr = factory.createAlgorithm("multithreaded", 100, 0.5);

    algPtr->getMap()->fromFile("input.txt", 1.0, "coordinates");

    mapCoroutine<double>::pull_type source([&](mapCoroutine<double>::push_type &yield)
                                           { algPtr->run(0, 10000, yield); });

    vector<size_t> bestPath = algPtr->getBestPath();

    for (auto &el : bestPath)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    std::cout << algPtr->calcBestPathLength(bestPath) << std::endl;

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