#include "antAlgorithms/basicAntAlgotiyhm.h"
#include "colonies/colony.h"
#include "maps/map.h"
#include "ants/basicAnt.h"
#include "chooseNextNodeStrategies/chooseStrategy.h"
#include "updateFeromoneStrategies/basicFeromoneDecayStrategy.h"
#include "chooseBestRootStrategies/chooseBestFeromoneRoot.h"
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
    Colony<double, double> col;
    ChooseStrategyFactory<double, double> strategyFactory;
    for (int i = 0; i < 100; i++)
    {

        std::unique_ptr<ChooseNextStrategy<double, double>> str = strategyFactory.createStrategy("basic", 1, 1);

        BasicAnt<double, double> ant(std::move(str)); // Create BasicAnt object with the moved ChooseNextStrategy

        std::unique_ptr<Ant<double, double>> ptr = std::make_unique<BasicAnt<double, double>>(std::move(ant)); // Move the BasicAnt object to unique_ptr
        col.addAnt(std::move(ptr));                                                                            // Move the unique_ptr to addAnt function
    }

    Map<double, double> map;

    std::unique_ptr<BasicFeromoneDecay<double, double>> basicDecay = std::make_unique<BasicFeromoneDecay<double, double>>(0.5);
    std::unique_ptr<UpdateFeromoneStrategy<double, double>> updateStrategy = std::move(basicDecay);

    map.randomInit(10, 1);

    std::unique_ptr<Map<double, double>> mapPtr = std::make_unique<Map<double, double>>(std::move(map));
    std::unique_ptr<Colony<double, double>> colPtr = std::make_unique<Colony<double, double>>(std::move(col));

    std::unique_ptr<ChooseBestFeromoneRoot<double, double>> chooseRootStrategy = std::make_unique<ChooseBestFeromoneRoot<double, double>>();
    std::unique_ptr<ChooseBestRootStrategy<double, double>> chooseRootStrategyPtr = std::move(chooseRootStrategy);

    BasicAntAlgorithm<double, double> alg(mapPtr,
                                          colPtr,
                                          updateStrategy,
                                          chooseRootStrategyPtr);

    mapCoroutine<double>::pull_type source([&](mapCoroutine<double>::push_type &yield)
                                           { alg.run(0, 100, yield); });

    vector<size_t> bestPath = alg.getBestPath();

    for (auto &el : bestPath)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    std::cout << alg.calcBestPathLength(bestPath) << std::endl;

    return 0;
}
