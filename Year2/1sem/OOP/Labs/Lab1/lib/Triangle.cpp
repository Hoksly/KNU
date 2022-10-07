#include "Triangle.hpp"

Triangle::Triangle(Point A, Point B, Point C)
{
    _A = A;
    _B = B;
    _C = C;
    Line l1;
    try
    {
        l1 = Line(A, B);
    }
    catch (std::invalid_argument)
    {
        throw std::invalid_argument("All three points in triangle must be different");
    }

    if (l1.passes_through(C))
    {
        throw std::invalid_argument("Points lie on a same line");
    }
}

std::string Triangle::str() const
{
    std::string s = "";
    s += "A" + _A.str();
    s += ", B" + _B.str();
    s += ", C" + _C.str();

    return s;
}

double Triangle::S() const
{
    // using geron formula

    double p_2 = P() / 2;

    return sqrt((p_2 - AB_len()) * (p_2 - AC_len()) * (p_2 - BC_len()) * p_2);
}

bool Triangle::has_same_points(const Triangle &T2) const
{
    // I don't know beter ways...
    if (A() == T2.A())
    {
        if (B() == T2.B())
        {
            if (C() == T2.C())
                return true;
        }

        if (B() == T2.C())
        {
            if (C() == T2.B())
                return true;
        }
    }

    if (A() == T2.B())
    {
        if (B() == T2.A())
        {
            if (C() == T2.C())
                return true;
        }
        if (B() == T2.C())
        {
            if (C() == T2.A())
                return true;
        }
    }

    if (A() == T2.C())
    {
        // std::cout << "CHECKING" << std::endl;
        if (B() == T2.B())
        {
            // std::cout << "CHECKING1" << std::endl;
            if (C() == T2.A())
                return true;
        }
        if (B() == T2.A())
        {
            // std::cout << "CHECKING2" << std::endl;
            if (C() == T2.B())
                return true;
        }
    }
    std::cout << str() << std::endl;
    std::cout << T2.str() << std::endl;
    std::cout << _B.str() << ' ' << T2.A().str() << std::endl;
    std::cout << _B.str() << ' ' << T2.B().str() << std::endl;
    std::cout << (int)(A() == T2.C()) << std::endl;
    // std::cout << (int)(_A == T2.C()) << std::endl;
    return false;
}

bool Triangle::operator==(const Triangle &T2) const
{
    return T2.S() == S() && P() == T2.P();
}