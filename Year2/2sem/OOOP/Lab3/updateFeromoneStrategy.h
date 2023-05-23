template <class feromoneT>
class UpdateFeromoneStrategy
{
public:
    virtual void updateFeromone(feromoneT decayCoeff) = 0;
};

template <class feromoneT, class distanceT>
class BasicFeromoneDecay : public UpdateFeromoneStrategy<feromoneT>
{
    void updateFeromone(feromoneT decayCoeff, Map<distanceT, feromoneT> &map)
    {
        vector<vector<feromoneT>> feromone = map.getFeromone();
        for (size_t i = 0; i < feromone.size(); ++i)
        {
            for (size_t j = 0; j < feromone.size(); ++j)
            {
                feromone[i][j] *= decayCoeff;
            }
        }
    }
};