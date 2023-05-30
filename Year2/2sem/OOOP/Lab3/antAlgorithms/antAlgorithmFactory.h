#include "antAlgorithm.h"
#include "basicAntAlgotiyhm.h"
#include "multyThreadedAlgorythm.h"

template <class feromoneT = double, class distanceT = double>
class AntAlgorithmFactory
{
protected:
    std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> createBasic(size_t antsCount,
                                                                    double decayCoeff, double PheromoneImpact,
                                                                    double distanceImpact)
    {
        Colony<double, double> col;
        ChooseStrategyFactory<double, double> strategyFactory;
        for (int i = 0; i < antsCount; i++)
        {

            std::shared_ptr<ChooseNextStrategy<double, double>> str = strategyFactory.createStrategy("basic",
                                                                                                     PheromoneImpact,
                                                                                                     distanceImpact);

            BasicAnt<double, double> ant(std::move(str)); // Create BasicAnt object with the moved ChooseNextStrategy

            std::shared_ptr<Ant<double, double>> ptr = std::make_unique<BasicAnt<double, double>>(std::move(ant)); // Move the BasicAnt object to unique_ptr
            col.addAnt(std::move(ptr));                                                                            // Move the unique_ptr to addAnt function
        }

        Map<double, double> map;

        std::shared_ptr<BasicFeromoneDecay<double, double>> basicDecay = std::make_unique<BasicFeromoneDecay<double, double>>(decayCoeff);
        std::shared_ptr<UpdateFeromoneStrategy<double, double>> updateStrategy = std::move(basicDecay);

        std::shared_ptr<Map<double, double>> mapPtr = std::make_unique<Map<double, double>>(std::move(map));
        std::shared_ptr<Colony<double, double>> colPtr = std::make_unique<Colony<double, double>>(std::move(col));

        std::shared_ptr<ChooseBestFeromoneRoot<double, double>> chooseRootStrategy = std::make_unique<ChooseBestFeromoneRoot<double, double>>();
        std::shared_ptr<ChooseBestRootStrategy<double, double>> chooseRootStrategyPtr = std::move(chooseRootStrategy);

        BasicAntAlgorithm<double, double> alg(mapPtr,
                                              colPtr,
                                              updateStrategy,
                                              chooseRootStrategyPtr);

        std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> algPtr = std::move(std::make_unique<BasicAntAlgorithm<feromoneT, distanceT>>(std::move(alg)));
        return algPtr;
    }

    std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> createMultythreaded(size_t antsCount,
                                                                            double decayCoeff, size_t threadsCount, double PheromoneImpact,  double distanceImpact)

    {
        Colony<double, double> col;
        ChooseStrategyFactory<double, double> strategyFactory;
        for (int i = 0; i < antsCount; i++)
        {

            std::shared_ptr<ChooseNextStrategy<double, double>> str = strategyFactory.createStrategy("basic",
                                                                                                     PheromoneImpact,
                                                                                                     distanceImpact);

            BasicAnt<double, double> ant(std::move(str)); // Create BasicAnt object with the moved ChooseNextStrategy

            std::shared_ptr<Ant<double, double>> ptr = std::make_unique<BasicAnt<double, double>>(std::move(ant)); // Move the BasicAnt object to unique_ptr
            col.addAnt(std::move(ptr));                                                                            // Move the unique_ptr to addAnt function
        }

        Map<double, double> map;

        std::shared_ptr<BasicFeromoneDecay<double, double>> basicDecay = std::make_unique<BasicFeromoneDecay<double, double>>(decayCoeff);
        std::shared_ptr<UpdateFeromoneStrategy<double, double>> updateStrategy = std::move(basicDecay);

        std::shared_ptr<Map<double, double>> mapPtr = std::make_unique<Map<double, double>>(std::move(map));
        std::shared_ptr<Colony<double, double>> colPtr = std::make_unique<Colony<double, double>>(std::move(col));

        std::shared_ptr<ChooseBestFeromoneRoot<double, double>> chooseRootStrategy = std::make_unique<ChooseBestFeromoneRoot<double, double>>();
        std::shared_ptr<ChooseBestRootStrategy<double, double>> chooseRootStrategyPtr = std::move(chooseRootStrategy);

        MultyThreadedAntAlgorithm<double, double> alg(mapPtr,
                                                      colPtr,
                                                      updateStrategy,
                                                      chooseRootStrategyPtr, threadsCount);

        std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> algPtr = std::move(std::make_unique<MultyThreadedAntAlgorithm<feromoneT, distanceT>>(std::move(alg)));
        return algPtr;
    }

public:
    AntAlgorithmFactory() = default;
    std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> createAlgorithm(std::string algorithmName,
                                                                        std::shared_ptr<Map<feromoneT, distanceT>> &map,
                                                                        std::shared_ptr<Colony<feromoneT, distanceT>> &colony,
                                                                        std::shared_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> &updateStrategy,
                                                                        std::shared_ptr<ChooseBestRootStrategy<feromoneT, distanceT>> &chooseRootStrategy)
    {
        if (algorithmName == "basic")
        {
            std::shared_ptr<BasicAntAlgorithm<feromoneT, distanceT>> ptr = std::make_unique<BasicAntAlgorithm<feromoneT, distanceT>>(map,
                                                                                                                                     colony,
                                                                                                                                     updateStrategy,
                                                                                                                                     chooseRootStrategy);
            std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> colPtr = std::move(ptr);
            return colPtr;
        }
        else if (algorithmName == "multithreaded")
        {
            std::shared_ptr<MultyThreadedAntAlgorithm<feromoneT, distanceT>> ptr = std::make_unique<MultyThreadedAntAlgorithm<feromoneT, distanceT>>(map,
                                                                                                                                                     colony,
                                                                                                                                                     updateStrategy,
                                                                                                                                                     chooseRootStrategy);
            std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> colPtr = std::move(ptr);
            return colPtr;
        }

        else
        {
            throw std::invalid_argument("Invalid algorithm name");
        }
    }

    std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> createAlgorithm(std::string algorithmName, size_t antsCount = 1000,
                                                                        double decayCoeff = 0.5, double pheromoneImpact = 1.0, double distanceImpact = 1.0, size_t threadsCount = 0)
    {
        if (algorithmName == "basic")
        {
            return createBasic(antsCount, decayCoeff, pheromoneImpact, distanceImpact);
        }
        else if (algorithmName == "multithreaded")
        {
            return createMultythreaded(antsCount, decayCoeff, threadsCount, pheromoneImpact, distanceImpact);
        }
        else
        {
            throw std::invalid_argument("Invalid algorithm name");
        }
    }
};