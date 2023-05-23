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
using mapCoroutine = boost::coroutines2::coroutine<std::vector<distanceT>>;

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
};

template <class feromoneT, class distanceT>
class BasicAntAlgorithm : public AntAlgorithm<feromoneT, distanceT>
{
public:
    BasicAntAlgorithm(std::unique_ptr<Map<distanceT, feromoneT>> &map,
                      std::unique_ptr<Colony<feromoneT, distanceT>> &colony,
                      std::unique_ptr<UpdateFeromoneStrategy<feromoneT, distanceT>> &updateStrategy)
        : AntAlgorithm<feromoneT, distanceT>(map, colony, updateStrategy) {}

    void run(size_t begin, size_t iterations);
};

template <class feromoneT, class distanceT>
void BasicAntAlgorithm<feromoneT, distanceT>::run(size_t begin, size_t iterations)
{
    for (size_t i = 0; i < iterations; ++i)
    {
        for (auto &ant : *(this->colony))
        {
            ant->run(begin, *this->map); // Call run method from BasicAnt
            for (const auto &node : ant->getPath())
            {

                std::cout << node << " " << std::flush;
            }
        }
        this->updateStrategy->updateFeromone(*this->map);
    }
}
