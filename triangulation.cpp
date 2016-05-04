#include "triangulation.h"

Triangulation::Triangulation() :
    m_points(),
    m_segments()
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

std::vector<Segment*> Triangulation::getSegments() const {
    return m_segments;
}

Segment* Triangulation::getSegment(int index) const {
    return m_segments.at(index);
}

void Triangulation::addSegment(Segment* s) {
    // TODO isLeft ?
}
