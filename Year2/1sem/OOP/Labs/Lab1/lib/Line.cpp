#include "Line.hpp"

Line::Line(Point A, Point B)
{
    // using A as x0 and y0
    // and B as x1 and y1
    _k = (B.y() - A.y()) / (B.x() - A.x());
    _b = (B.y() - A.y()) / (B.x() - A.x()) * (-A.x()) + A.y();
}

Line::Line(Point A, Vector v)
{
    _k = v.y() / v.x();
    _b = (-A.x() * v.y()) / v.x() + A.y();
}

std::string Line::str()
{
    std::string s = "y = ";

    s += std::to_string(_k) + " + ";
    s += std::to_string(_b);

    return s;
}

std::pair<double, double> Line::pair()
{
    return std::make_pair(_k, _b);
}

std::vector<Point> Line::intercept(Line B)
{

    std::vector<Point> Points;

    // they are parallel or same

    if (this->_k - B._k == 0 || this->_k / this->_b == B._k / B._b)
        return Points;

    double x0 = (B._b - this->_b) / (this->_k - B._k); // x0 = (b2 - b1) / (x1 - x2)
    double y0 = this->_k * x0 + this->_b;              // y0 = k1 * x0 + b1

    Points.push_back(Point(x0, y0));

    return Points;
}

bool Line::passes_through(Point A)
{
    if (A.y() == this->_k * A.x() + this->_b)
        return true;
    return false;
}
bool Line::is_paralel(Line l1)
{
    return this->_k == l1._k;
}

Vector Line::normal_vecor()
{
    double x, y;
    if (_b != 0)
    {
        x = -(this->_b) / this->_k;
        y = this->_b;
        return Vector(x, y);
    }

    Point A = random_point();
    Point B = random_point();
    while (A == B)
        B = random_point();

    Vector dest_V(A, B);
    dest_V.rotate_90();
    return dest_V;
}

Point Line::random_point()
{
    srand(time(NULL));

    double random_x = rand() % 100;
    double random_y = _k * random_x + _b;

    return Point(random_x, random_y);
}
