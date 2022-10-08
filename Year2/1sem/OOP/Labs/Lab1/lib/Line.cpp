#include "Line.hpp"

std::vector<double> Line::__solve_quadratic_eqasion(double a, double b, double c)
{
    double D = pow(b, 2) - 4 * a * c;
    std::vector<double> results;
    if (D > 0)
    {
        results.push_back((-b + sqrt(D)) / (2 * a));
        results.push_back((-b - sqrt(D)) / (2 * a));
    }

    else if (D == 0)
    {
        results.push_back(-b / (2 * a));
    }

    return results;
}

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

std::string Line::str() const
{

    std::string s = "";
    if (_angle == M_PI_2)
    {
        s += "x = " + std::to_string(_b);
        return s;
    }
    s += "y = ";

    s += std::to_string(_k) + "x + ";
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

std::vector<Point> Line::intercept(Circle C)
{
    std::vector<Point> points;

    if (_angle != M_PI_2)
    {
        std::vector<double> X_of_interceptions = __solve_quadratic_eqasion(
            pow(_k, 2) + 1,
            (2 * _b * _k) - (2 * _k * C.O().y()) - 2 * C.O().x(),
            pow(_b, 2) - pow(C.r(), 2) + pow(C.O().x(), 2) - 2 * _b * C.O().y() + pow(C.O().y(), 2));

        for (double x : X_of_interceptions)
        {
            points.push_back(Point(x, _k * x + _b));
        }
    }
    else
    {
        std::vector<double> Y_of_interceptions = __solve_quadratic_eqasion(
            1,
            2 * C.O().y(),
            -pow(C.r(), 2) + pow(_b - C.O().x(), 2));

        for (double y : Y_of_interceptions)
        {
            points.push_back(Point(_b, y));
        }
    }

    return points;
}

bool Line::passes_through(Point A)
{
    if (this->_angle == M_PI_2)
    {
        if (A.x() == _b)
            return true;
        return false;
    }
    if (fabs(A.y() - (this->_k * A.x() + this->_b)) < 1.e-5)
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
