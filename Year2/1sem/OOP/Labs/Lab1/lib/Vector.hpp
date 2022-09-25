#include <string>

class Vector
{
    double _x, _y;

public:
    // Constructors
    Vector(double x, double y) : _x(x), _y(y) {}
    Vector(std::pair<double, double> p) _x(p.first), _y(p.second) {}

    // Getters
    inline double x() { return _x; }
    inline double y() { return _y; }

    // Other Methods
    void scale_to(double target_len);
};