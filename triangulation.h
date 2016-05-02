#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>

#include "point.h"

class Triangulation
{
public:
    Triangulation();
    std::vector<Point*> getPoints() const;

private:
    std::vector<Point*> m_points;
};

#endif // TRIANGULATION_H
