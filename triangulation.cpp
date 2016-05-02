#include "triangulation.h"

Triangulation::Triangulation()
{
}

std::vector<Point*> Triangulation::getPoints() const {
    return m_points;
}
