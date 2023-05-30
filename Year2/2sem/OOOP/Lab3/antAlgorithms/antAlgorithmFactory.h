#include "antAlgorithm.h"
#include "basicAntAlgotiyhm.h"
#include "multyThreadedAlgorythm.h"

template <class feromoneT = double, class distanceT = double>
class AntAlgorithmFactory
{
protected:
    std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> createBasic(size_t antsCount,
                                                                    double decayCoeff, double PheromoneImpact,
                                                                    double distanceImpact, double  pheromoneSpread)
    {
        Colony< feromoneT,  distanceT> col;
        ChooseStrategyFactory< feromoneT,  distanceT> strategyFactory;
        for (int i = 0; i < antsCount; i++)
        {

            std::shared_ptr<ChooseNextStrategy< feromoneT,  distanceT>> str = strategyFactory.createStrategy("basic",
                                                                                                     PheromoneImpact,
                                                                                                     distanceImpact);

            BasicAnt< feromoneT,  distanceT> ant(std::move(str), pheromoneSpread); // Create BasicAnt object with the moved ChooseNextStrategy

            std::shared_ptr<Ant< feromoneT,  distanceT>> ptr = std::make_unique<BasicAnt< feromoneT,  distanceT>>(std::move(ant)); // Move the BasicAnt object to unique_ptr
            col.addAnt(std::move(ptr));                                                                            // Move the unique_ptr to addAnt function
        }

        Map< feromoneT,  distanceT> map;

        std::shared_ptr<BasicFeromoneDecay< feromoneT,  distanceT>> basicDecay = std::make_unique<BasicFeromoneDecay< feromoneT,  distanceT>>(decayCoeff);
        std::shared_ptr<UpdateFeromoneStrategy< feromoneT,  distanceT>> updateStrategy = std::move(basicDecay);

        std::shared_ptr<Map< feromoneT,  distanceT>> mapPtr = std::make_unique<Map< feromoneT,  distanceT>>(std::move(map));
        std::shared_ptr<Colony< feromoneT,  distanceT>> colPtr = std::make_unique<Colony< feromoneT,  distanceT>>(std::move(col));

        std::shared_ptr<ChooseBestFeromoneRoot< feromoneT,  distanceT>> chooseRootStrategy = std::make_unique<ChooseBestFeromoneRoot< feromoneT,  distanceT>>();
        std::shared_ptr<ChooseBestRootStrategy< feromoneT,  distanceT>> chooseRootStrategyPtr = std::move(chooseRootStrategy);

        BasicAntAlgorithm< feromoneT,  distanceT> alg(mapPtr,
                                              colPtr,
                                              updateStrategy,
                                              chooseRootStrategyPtr);

        std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> algPtr = std::move(std::make_unique<BasicAntAlgorithm<feromoneT, distanceT>>(std::move(alg)));
        return algPtr;
    }

    std::shared_ptr<AntAlgorithm<feromoneT, distanceT>> createMultythreaded(size_t antsCount,
                                                                            double decayCoeff, size_t threadsCount,
                                                                            double PheromoneImpact,  double distanceImpact,
                                                                            double  pheromoneSpread)

    {
        Colony< feromoneT,  distanceT> col;
        ChooseStrategyFactory< feromoneT,  distanceT> strategyFactory;
        for (int i = 0; i < antsCount; i++)
        {

            std::shared_ptr<ChooseNextStrategy< feromoneT,  distanceT>> str = strategyFactory.createStrategy("basic",
                                                                                                     PheromoneImpact,
                                                                                                     distanceImpact);

            BasicAnt< feromoneT,  distanceT> ant(std::move(str), pheromoneSpread); // Create BasicAnt object with the moved ChooseNextStrategy

            std::shared_ptr<Ant< feromoneT,  distanceT>> ptr = std::make_unique<BasicAnt< feromoneT,  distanceT>>(std::move(ant)); // Move the BasicAnt object to unique_ptr
            col.addAnt(std::move(ptr));                                                                            // Move the unique_ptr to addAnt function
        }

        Map< feromoneT,  distanceT> map;

        std::shared_ptr<BasicFeromoneDecay< feromoneT,  distanceT>> basicDecay = std::make_unique<BasicFeromoneDecay< feromoneT,  distanceT>>(decayCoeff);
        std::shared_ptr<UpdateFeromoneStrategy< feromoneT,  distanceT>> updateStrategy = std::move(basicDecay);

        std::shared_ptr<Map< feromoneT,  distanceT>> mapPtr = std::make_unique<Map< feromoneT,  distanceT>>(std::move(map));
        std::shared_ptr<Colony< feromoneT,  distanceT>> colPtr = std::make_unique<Colony< feromoneT,  distanceT>>(std::move(col));

        std::shared_ptr<ChooseBestFeromoneRoot< feromoneT,  distanceT>> chooseRootStrategy = std::make_unique<ChooseBestFeromoneRoot< feromoneT,  distanceT>>();
        std::shared_ptr<ChooseBestRootStrategy< feromoneT,  distanceT>> chooseRootStrategyPtr = std::move(chooseRootStrategy);

        MultyThreadedAntAlgorithm< feromoneT,  distanceT> alg(mapPtr,
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
                                                                        double decayCoeff = 0.5, double pheromoneImpact = 1.0,
                                                                        double distanceImpact = 1.0, double pheromoneSpread = 1, size_t threadsCount = 0)
    {
        if (algorithmName == "basic")
        {
            return createBasic(antsCount, decayCoeff, pheromoneImpact, distanceImpact, pheromoneSpread);
        }
        else if (algorithmName == "multithreaded")
        {
            return createMultythreaded(antsCount, decayCoeff, threadsCount, pheromoneImpact, distanceImpact, pheromoneSpread);
        }
        else
        {
            throw std::invalid_argument("Invalid algorithm name");
        }
    }
};