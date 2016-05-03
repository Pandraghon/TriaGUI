#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

class Segment
{
public:
    Segment(Point* p1, Point* p2);

private:
    Point* m_points[2];
};

#endif // SEGMENT_H
