#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>

#include "point.h"
#include "segment.h"

class Triangulation
{
public:
    Triangulation();
    std::vector<Point*> getPoints() const;
    Point* getPoint(int index) const;
    void addPoint(Point* p);

private:
    std::vector<Point*> m_points;
    std::vector<Segment*> m_segments;
};

#endif // TRIANGULATION_H
