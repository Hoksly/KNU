#include "Line.hpp"
class Segment
{
    Line _l;
    Point _beg, _end;

public:
    Segment(Line l, Point A, Point B);
    Segment(Point A, Point B);
};