#include <vector>
#include <random>

using std::vector;
#ifndef MAP_H
#define MAP_H

template <class feromoneT, class distanceT>
class Map
{
    vector<vector<feromoneT>> feromone;
    vector<vector<distanceT>> distance;

public:
    Map() = default;
    Map(vector<std::pair<distanceT, distanceT>> points, feromoneT initFeromone);

    void randomInit(size_t size, feromoneT initFeromone);

    inline vector<vector<feromoneT>> &getFeromone() { return feromone; }
    inline vector<vector<distanceT>> &getDistance() { return distance; }

    inline vector<feromoneT> &getFeromone(size_t y) { return feromone[y]; }
    inline vector<distanceT> &getDistance(size_t y) { return distance[y]; }

    inline feromoneT &getFeromone(size_t y, size_t x) { return feromone[y][x]; }
    inline distanceT &getDistance(size_t y, size_t x) { return distance[y][x]; }

    inline size_t size() const { return feromone.size(); }

    inline void updateFeromone(feromoneT decayCoeff);
};

template <class feromoneT, class distanceT>
void Map<feromoneT, distanceT>::randomInit(size_t size, feromoneT initFeromone)
{
    feromone.resize(size);
    distance.resize(size);

    for (size_t i = 0; i < size; ++i)
    {
        feromone[i].resize(size);
        distance[i].resize(size);
    }
    distanceT randDist;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<distanceT> distribution(0.0, 1.0);

    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            randDist = distribution(generator);

            feromone[i][j] = feromone[j][i] = initFeromone;
            distance[i][j] = distance[j][i] = randDist;
        }
    }
}
#endif