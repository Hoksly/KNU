#include "Figure.hpp"
#include "Line.hpp"
#ifndef _SEGMENT_HPP
#define _SEGMENT_HPP
class Segment
{
    Line _l;
    Point _beg, _end;

public:
    Segment(Line l, Point A, Point B);
    Segment(Point A, Point B);
};

#endif
