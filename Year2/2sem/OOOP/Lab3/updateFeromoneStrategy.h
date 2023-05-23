template <class feromoneT, class distanceT>
class UpdateFeromoneStrategy
{
public:
    virtual void updateFeromone(Map<distanceT, feromoneT> &map) = 0;
};

template <class feromoneT, class distanceT>
class BasicFeromoneDecay : public UpdateFeromoneStrategy<feromoneT, distanceT>
{
private:
    feromoneT decayCoeff;

public:
    BasicFeromoneDecay() = default;
    BasicFeromoneDecay(feromoneT decayCoeff) : decayCoeff(decayCoeff) {}

    void updateFeromone(Map<distanceT, feromoneT> &map) override
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