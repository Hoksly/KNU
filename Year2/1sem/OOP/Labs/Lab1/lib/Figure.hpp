// just an abstract class
#include <string>

#ifndef _FIGURE_HPP
#define _FIGURE_HPP
class Figure
{
    std::string _figure_name;

    virtual std::string str() const { return "Basic Figure"; };
};

#endif