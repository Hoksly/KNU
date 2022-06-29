#pragma once
#include "functions.hpp"
#include "TypesAndDefinitions.hpp"
#include "AntMapClass.hpp"
#include <vector>
#include <random>
#include <string.h>
#include <algorithm>

struct Ant
{
    std::vector<uchar> path;
    uchar current_node;
    bool *allowed = nullptr;
    uchar *Path = nullptr;

    inline void go_to(uchar node, uchar iter);
    uchar choose_next(bool *allowed, AntMap &Map, uchar from, uchar n);
    void move(uchar begin, AntMap &Map);
    void update(uchar n);
    uchar *give_shortest(uchar i, AntMap &);
    ~Ant();
    Ant(uchar n);
    Ant() = default;

    inline uchar give_nearest(uchar beg, AntMap &Map);
};