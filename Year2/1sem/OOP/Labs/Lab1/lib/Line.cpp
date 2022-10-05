#include "Line.hpp"

Line::Line(Point A, Point B)
{
    // using A as x0 and y0
    // and B as x1 and y1
    if (A == B)
        throw std::invalid_argument("Two equal points given");

    if (B.x() != A.x())
    {
        _k = (B.y() - A.y()) / (B.x() - A.x());
        _b = (B.y() - A.y()) / (B.x() - A.x()) * (-A.x()) + A.y();
        _angle = atan(_k);
    }
    else // in this case we'll use x = b
    {
        _k = INFINITY;
        _b = B.x();
        _angle = M_PI_2;
    }
}

Line::Line(Point A, Vector v)
{
    if (v.x() != 0)
    {
        _k = v.y() / v.x();
        _b = (-A.x() * v.y()) / v.x() + A.y();
        _angle = atan(_k);
    }
    else
    {
        _angle = M_PI_2;
        _k = INFINITY;
        _b = A.x();
    }
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

    if (this->_angle == M_PI_2 && B._angle == M_PI_2)
    {

        return Points;
    }

    if (this->_angle - B._angle == 0) // paralel
    {
        std::cout << this->angle() << ' ' << B.angle() << std::endl;
        return Points;
    }

    if (this->_angle == M_PI_2)
    {

        double y = B.k() * this->b() + B.b();
        Points.push_back(Point(B.b(), y));

        return Points;
    }
    if (B.angle() == M_PI_2)
    {

        double y = this->k() * B.b() + this->b();
        Points.push_back(Point(this->b(), y));
        return Points;
    }

    double x0 = (B._b - this->_b) / (this->_k - B._k); // x0 = (b2 - b1) / (k1 - k2)
    double y0 = this->_k * x0 + this->_b;              // y0 = k1 * x0 + b1

    Points.push_back(Point(x0, y0));

    return Points;
}

bool Line::passes_through(Point A)
{
    if (this->_angle == M_PI_2)
    {
        if (A.x() == _b)
            return true;
        return false;
    }
    if (A.y() == this->_k * A.x() + this->_b)
        return true;
    return false;
}
bool Line::is_paralel(Line l1)
{
    return this->_angle == l1._angle;
}

Vector Line::normal_vecor()
{
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
    if (this->angle() == M_PI_2)
    {
        return Point(_b, rand() % 100);
    }

    double random_x = rand() % 100;
    double random_y = _k * random_x + _b;

    return Point(random_x, random_y);
}
