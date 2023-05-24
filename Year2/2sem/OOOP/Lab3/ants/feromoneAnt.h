#include "ant.h"

template <class feromoneT, class distanceT>
class FeromoneAnt : public Ant<feromoneT, distanceT>
{
    std::unique_ptr<ChooseNextStrategy<feromoneT, distanceT>> chooseStrat;
    size_t choose(std::size_t curNode, Map<distanceT, feromoneT> &);
    size_t curNode;
    vector<bool> available;

    size_t choose(Map<distanceT, feromoneT> &map)
    {
        return chooseStrat->choose(curNode, map, available);
    }
};
