#include "point.h"

Point::Point() : Point(0, 0) {}

Point::Point(float x, float y) :
    m_x(x),
    m_y(y),
    m_neighbors()
{}

void Point::addNeighbor(Point* p) {
    // add p only if not already present in m_neighbors
    if(std::find(m_neighbors.begin(), m_neighbors.end(), p) == m_neighbors.end()) {
        m_neighbors.push_back(p);
    }
}

void Point::setX(float x) {
    m_x = x;
}

void Point::setY(float y) {
    m_y = y;
}

float Point::getX() const {
    return m_x;
}

float Point::getY() const {
    return m_y;
}

// TODO : vérifier si y croissant
bool Point::isBefore(Point *p) const {
    return m_x < p->m_x || m_x == p->m_x && m_y < p->m_y;
}
