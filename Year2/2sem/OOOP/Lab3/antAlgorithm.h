template <class feromoneT, class distanceT>
class AntAlgorithm
{
    Map<distanceT, feromoneT> map;
    Colony<distanceT, feromoneT> colony;
    ChooseNextStrategy<distanceT, feromoneT> chooseStrategy;
    UpdateFeromoneStrategy<distanceT, feromoneT> updateStrategy;
};

template <class feromoneT, class distanceT>
class BasicAntAlgorithm : public AntAlgorithm<feromoneT, distanceT>
{
    Map<distanceT, feromoneT> map;
    Colony<distanceT, feromoneT> colony;
    ChooseNextStrategy<distanceT, feromoneT> chooseStrategy;
    UpdateFeromoneStrategy<distanceT, feromoneT> updateStrategy;
};