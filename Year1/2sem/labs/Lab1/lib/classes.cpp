#include "classes.hpp"

command::command(std::string s1, std::string s2, int num,  bool c_end)
{
    first = s1;
    second = s2;
    is_end = c_end;
    n = num;
    
}

