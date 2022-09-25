
#include "Point.hpp"
#include <string>
#include <vector>
#include "Vector.hpp"
class Line
{
    // y = kx + b
    double _k;
    double _b;

public:
    Line(Point A, Point B);
    std::string str();
    std::pair<double, double> pair();

    std::vector<Point> intercept(Line);
    bool passes_through(Point);

    Vector normal_vecor();
};