#include "Figure.hpp"
#include "Point.hpp"
#include "Line.hpp"
#ifndef _TRIANGLE_HPP
#define _TRIANGLE_HPP
class Triangle : Figure
{
private:
    Point _A, _B, _C;

public:
    Triangle(Point A, Point B, Point C);
    Point A() const { return _A; }
    Point B() const { return _B; }
    Point C() const { return _C; }

    inline double AB_len() const { return sqrt(pow(_A.x() - _B.x(), 2) + pow(_A.y() - _B.y(), 2)); }
    inline double AC_len() const { return sqrt(pow(_A.x() - _C.x(), 2) + pow(_A.y() - _C.y(), 2)); }
    inline double BC_len() const { return sqrt(pow(_C.x() - _B.x(), 2) + pow(_C.y() - _B.y(), 2)); }

    inline double P() const { return AB_len() + AC_len() + BC_len(); }

    bool has_same_points(const Triangle &T2) const;
    bool operator==(const Triangle &T2) const;
    double S() const;

    std::string str() const override;
};

#endif