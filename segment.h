#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

class Segment
{
public:
    Segment(Point* p1, Point* p2);
    bool isBefore(Segment* s) const;
    Point* getP0() const;
    Point* getP1() const;
    std::string getNom() const;
    void print() const;

private:
    Point* m_points[2];
    std::string m_nom;
};

#endif // SEGMENT_H
