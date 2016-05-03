#include "segment.h"

Segment::Segment(Point *p1, Point *p2)
{
    if(p1->isBefore(p2)) {
        m_points[0] = p1;
        m_points[1] = p2;
    } else {
        m_points[0] = p2;
        m_points[1] = p1;
    }
}
