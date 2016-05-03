#include "triangulation.h"

Triangulation::Triangulation()
{
}

std::vector<Point*> Triangulation::getPoints() const {
    return m_points;
}

Point* Triangulation::getPoint(int index) const {
    return m_points.at(index);
}

void Triangulation::addPoint(Point* p) {
    if(m_points.size() == 0) m_points.push_back(p);
    else {
        std::vector<Point*>::reverse_iterator it;
        for(it = m_points.rbegin() ; it != m_points.rend() && p->isBefore((Point*)*it) ; ++it);
        if(p != *it) m_points.insert(it.base(), p);
    }
}
