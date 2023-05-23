#include "antAlgorithm.h"
#include "colony.h"
#include "basicAnt.h"
#include "chooseStrategy.h"

#include "map.h"
#include <iostream>
#include <memory>

int main()
{
    Colony<double, double> col;

    for (int i = 0; i < 100; i++)
    {
        std::unique_ptr<BasicChooseStrategy<double, double>> basicStrat = std::make_unique<BasicChooseStrategy<double, double>>(1, 1);
        std::unique_ptr<ChooseNextStrategy<double, double>> str = std::move(basicStrat);

        BasicAnt<double, double> ant(std::move(str)); // Create BasicAnt object with the moved ChooseNextStrategy

        std::unique_ptr<Ant<double, double>> ptr = std::make_unique<BasicAnt<double, double>>(std::move(ant)); // Move the BasicAnt object to unique_ptr
        col.addAnt(std::move(ptr));                                                                            // Move the unique_ptr to addAnt function
    }

    Map<double, double> map;

    map.randomInit(10, 1);
    AntAlgorithm<double, double> alg();
    return 0;
}
