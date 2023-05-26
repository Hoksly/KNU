#include <vector>
#include <random>
#include <iostream>

using std::vector;
#ifndef MAP_H
#define MAP_H

template <class feromoneT, class distanceT>
class Map
{
    vector<vector<feromoneT>> feromone;
    vector<vector<distanceT>> distance;

    void fromCoordinates(const vector<std::pair<distanceT, distanceT>> &points, feromoneT initFeromone);

public:
    Map() = default;
    Map(const vector<std::pair<distanceT, distanceT>> &points, feromoneT initFeromone);
    Map(std::string filename, feromoneT initFeromone, std::string mode = "coordinates");
    void randomInit(size_t size, feromoneT initFeromone);

    inline vector<vector<feromoneT>> &getFeromone() { return feromone; }
    inline vector<vector<distanceT>> &getDistance() { return distance; }

    inline vector<feromoneT> &getFeromone(size_t y) { return feromone[y]; }
    inline vector<distanceT> &getDistance(size_t y) { return distance[y]; }

    inline feromoneT &getFeromone(size_t y, size_t x) { return feromone[y][x]; }
    inline distanceT &getDistance(size_t y, size_t x) { return distance[y][x]; }

    inline size_t size() const { return feromone.size(); }

    inline void updateFeromone(feromoneT decayCoeff);

    inline void fromFile(std::string filename, feromoneT initFeromone, std::string mode = "coordinates");
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

template <class feromoneT, class distanceT>
void Map<feromoneT, distanceT>::fromCoordinates(const vector<std::pair<distanceT, distanceT>> &points, feromoneT initFeromone)
{
    feromone.resize(points.size());
    distance.resize(points.size());

    for (size_t i = 0; i < points.size(); ++i)
    {
        feromone[i].resize(points.size());
        distance[i].resize(points.size());
    }

    for (size_t i = 0; i < points.size(); ++i)
    {
        feromone[i][i] = 0;
        distance[i][i] = 0;
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            feromone[i][j] = feromone[j][i] = initFeromone;
            distance[i][j] = distance[j][i] = sqrt(pow(points[i].first - points[j].first, 2) + pow(points[i].second - points[j].second, 2));
        }
    }
}

template <class feromoneT, class distanceT>
Map<feromoneT, distanceT>::Map(const vector<std::pair<distanceT, distanceT>> &points, feromoneT initFeromone)
{
    fromCoordinates(points, initFeromone);
}

template <class feromoneT, class distanceT>
void Map<feromoneT, distanceT>::fromFile(std::string filename, feromoneT initFeromone, std::string mode)
{
    std::freopen(filename.c_str(), "r", stdin);

    size_t nodes;
    std::cin >> nodes;
    vector<std::pair<distanceT, distanceT>> points(nodes);

    points.resize(nodes);

    for (size_t i = 0; i < nodes; ++i)
    {
        std::cin >> points[i].first >> points[i].second;
    }
    fromCoordinates(points, initFeromone);
}

template <class feromoneT, class distanceT>
Map<feromoneT, distanceT>::Map(std::string filename, feromoneT initFeromone, std::string mode)
{
    if (mode == "coordinates")
    {
        fromFile(filename, initFeromone, mode);
    }
    else
    {
        throw std::invalid_argument("Invalid mode");
    }
}

#endif