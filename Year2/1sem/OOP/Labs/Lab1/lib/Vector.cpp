#include "Vector.hpp"

void Vector::scale_to(double target_len)
{
    double cur_len = sqrt(pow(_x, 2) + pow(_y, 2));
    double mult = target_len / cur_len;
    _x *= mult;
    _y *= mult;
}

Vector Vector::operator+(Vector b)
{
    return Vector(this->_x + b._x, this->_y + b._y);
}

Vector Vector::operator-(Vector b)
{
    return Vector(this->_x - b._x, this->_y - b._y);
}

std::string Vector::str()
{
    std::string s = "(";
    s += std::to_string(_x) + ", ";
    s += std::to_string(_y) + ")";
    return s;
}

std::pair<double, double> Vector::pair()
{
    return std::make_pair(_x, _y);
}

void Vector::print()
{
    std::cout << this->str() << '\n';
}