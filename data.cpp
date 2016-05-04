#include "data.h"

Data::Data() :
    m_triangs(1, new Triangulation()),
    m_points()
{
    m_triangs[0]->addPoint(new Point());
    m_triangs[0]->addPoint(new Point(1, 5));
    m_triangs[0]->addPoint(new Point(1, 1));
}

Data::~Data() {
    for(unsigned int i{} ; i < m_triangs.size() ; ++i) delete m_triangs[i];
    for(unsigned int i{} ; i < m_points.size() ; ++i) delete m_points[i];
}

std::vector<Triangulation*> Data::getTriangulations() const {
    return m_triangs;
}

Triangulation *Data::getTriangulation(int index) const {
    return m_triangs.at(index);
}
