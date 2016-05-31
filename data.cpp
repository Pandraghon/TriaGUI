#include "data.h"

Data::Data() :
    m_triangs(1, new Triangulation()),
    m_points()
{
    m_triangs[0]->addPoint(new Point());
    m_triangs[0]->addPoint(new Point(10, 10));
    m_triangs[0]->addPoint(new Point(10, 0));
    m_triangs[0]->addPoint(new Point(0, 10));
    m_triangs[0]->addPoint(new Point(-10, -10));
    m_triangs[0]->addPoint(new Point(-10, 0));
    m_triangs[0]->addPoint(new Point(0, -10));
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

int Data::nbTriangulation() const {
    return m_triangs.size();
}

void Data::addTriangulation(Triangulation *t) {
    this->m_triangs.push_back(t);
}

void Data::nextOrder() {
    m_triangs.push_back(new Triangulation(this));
}


std::ostream &operator<<(std::ostream &out, const Data &v) {
    out << v.m_triangs.size() << std::endl;
    for(Triangulation* t : v.m_triangs) {
        out << *t << std::endl;
    }
//    out << v.m_triangs.size();
//    for(Triangle* t : v.m_triangs)
//        out << t->getNom()
//            << t->
    return out;
}


std::istream &operator>>(std::istream &in, Data &v) {
    int pointsSize{};
    Point p;
    in >> pointsSize;
    v.m_points.resize(pointsSize);
    for(int i{} ; i < pointsSize ; ++i) {
        in >> p;
        v.m_points[i] = new Point(p.getX(), p.getY());
    }
    return in;
}
