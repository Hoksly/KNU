#include "Circle.hpp"

Point Circle::random_point()
{
    srand(time(NULL));

    double random_value = (rand() % 100) * 0.02 - 1; // in range (-1, 1)

    double x = _O.x() + _r * random_value;

    double y = sqrt(pow(_r, 2) - pow(_O.x() - x, 2)) + _O.y();

    return Point(x, y);
}