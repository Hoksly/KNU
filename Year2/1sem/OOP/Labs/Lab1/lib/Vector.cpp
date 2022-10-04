#include "Vector.hpp"

Vector::Vector(Point A, Point B)
{
    // vector with start at point A and end in B

    _x = B.x() - A.x();
    _y = B.y() - A.y();
}
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

void Vector::rotate_right(double angle)
{
    double x2, y2;
    x2 = cos(angle) * _x - sin(angle) * _y;
    y2 = sin(angle) * _x + cos(angle) * _y;

    _x = x2;
    _y = y2;
}
void Vector::rotate_90()
{
    rotate_right(M_PI / 2);
}

void Vector::print()
{
    std::cout << this->str() << '\n';
}