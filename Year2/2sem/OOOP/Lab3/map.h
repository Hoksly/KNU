#include <vector>
using std::vector;

template <class feromoneT, class distanceT>
class Map
{
    vector<vector<feromoneT>> feromone;
    vector<vector<distanceT>> distance;

public:
    Map(vector<std::pair<distanceT, distanceT>> points, feromoneT initFeromone);

    inline vector<feromoneT> getFeromone(size_t y) { return feromone[y]; }
    inline vector<distanceT> getDistance(size_t y) { return distance[y]; }

    inline void updateFeromone(feromoneT decayCoeff);
};