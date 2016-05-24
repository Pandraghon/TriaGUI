#include "triangulation.h"
#include <iostream>

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

void Triangulation::addPoints(Point** p, int size){
    for(int i=0; i<size; i++){
        this->addPoint(p[i]);
    }
}

std::vector<Segment*> Triangulation::getSegments() const {
    return m_segments;
}

Segment* Triangulation::getSegment(int index) const {
    return m_segments.at(index);
}

void Triangulation::addSegment(Segment* s) {
    if(m_segments.size() == 0) m_segments.push_back(s);
    else {
        std::vector<Segment*>::reverse_iterator it;
        for(it = m_segments.rbegin() ; it != m_segments.rend() && s->isBefore((Segment*)*it) ; ++it);
        if(s != *it) m_segments.insert(it.base(), s);
    }
}

void Triangulation::addSegments(Segment** s, int size) {
    for(int i=0; i<size; i++){
        this->addSegment(s[i]);
    }
}

void Triangulation::addTriangle(Triangle *t)
{
    m_triangles.push_back(t);
}

void Triangulation::print() const{
    std::cout<<"Triangulation:"<<std::endl;
    std::cout<<"Points:"<<std::endl;
    for(int i=0; i<m_points.size(); i++){
        m_points[i]->print();
    }
    std::cout<<"Segments:";
    for(int i=0; i<m_segments.size(); i++){
        m_segments[i]->print();
        std::cout<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Triangles:";
    for(int i=0; i<m_triangles.size(); i++){
        m_triangles[i]->print();
        std::cout<<" ";
    }
    std::cout<<std::endl;
}

void Triangulation::scanTriangles()
{   Point *pointCourant;
    Segment *segCourant;
    //pour chaque segment
    //std::cout << m_segments.size() << " segments" << std::endl;

    for(int s=0; s<this->m_segments.size(); s++){
        segCourant=this->m_segments[s];
        pointCourant=segCourant->getP0();
        std::cout<<"Segment courant: "<<segCourant->getNom()<<std::endl;
        if (m_segments.at(s+1)->getP0()==pointCourant){
//            if( segCourant->getP1()->isSegment( m_segments[s+1]->getP1() ))
            {
                Triangle *t = new Triangle(pointCourant, segCourant->getP1(), m_segments[s+1]->getP1());
                this->addTriangle( t );
                t->print();
                std::cout<<std::endl;
            }
        }
    }
}
