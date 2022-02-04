#pragma once
#include <string>

struct command
{
    std::string first;
    std::string second;
    bool is_end;
    int n;

    command(std::string, std::string, int , bool); 
};
