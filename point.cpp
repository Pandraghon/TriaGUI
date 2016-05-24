#include "point.h"
#include "segment.h"
#include <iostream>

int Point::nb=0;

Point::Point() : Point(0, 0) {}

Point::Point(float x, float y) :
    m_x(x),
    m_y(y),
//    m_neighbors(),
    m_segments(),
    m_nom("P")
{
    m_nom += std::to_string(nb++);
}

/*void Point::addNeighbor(Point* p) {
    // add p only if not already present in m_neighbors
    if(std::find(m_neighbors.begin(), m_neighbors.end(), p) == m_neighbors.end()) {
        m_neighbors.push_back(p);
    }
}*/

//il faut ajouter ce point de façon a ce que le tableau soit trier dans l'ordre trigo
void Point::addSegment(Segment* s)  {
    if(std::find(m_segments.begin(), m_segments.end(), s) == m_segments.end()) {
        m_segments.push_back(s);
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


// a tester
bool Point::isLeft(Point* p, Point* q) const{
    double det= p->getX()*q->getY() + q->getX()*this->getY() + this->getX()*p->getY()
            - this->getX()*q->getY() - p->getX()*this->getY() - q->getX()*p->getY();
/*    std::cout << "|" << p->getX() << " " << p->getY() << "|" << std::endl
              << "|" << q->getX() << " " << q->getY() << "|" << std::endl
              << "|" << this->getX() << " " << this->getY() << "|" << std::endl;
    std::cout << p->getX() << "*" << q->getY() << " + " << q->getX() << "*" << this->getY() << " + " << this->getX() << "*" << p->getY()
              << " - " << this->getX() << "*" << q->getY() << " - " << p->getX() << "*" << this->getY() << " - " << q->getX() << "*" << p->getY() << std::endl;
    std::cout<<"det = "<<det<<std::endl;
    */
    return det>0;
}

bool Point::isLeft(const Segment *pq) const {
    return (this->isLeft(pq->getP0(), pq->getP1()));
}

bool Point::isSegment(Point *p)
{   Point* p0, *p1;
    if(this->isBefore(p)) { p0=this; p1=p;}
    else { p0=p; p1=this;}
    for(int i=0; i<p0->m_segments.size(); i++){
        if( p0->m_segments[i]->getP1()==p1)
            return true;
    }
    return false;
}

std::string Point::getNom() const{
    return m_nom;
}

void Point::print() const {
    std::cout<<m_nom<<": ("<<this->getX()<<','<<this->getY()<<')'<<std::endl;
    if (m_segments.size()>0){

        std::cout<<"Segments: { ";
        for(int i=0; i<m_segments.size(); i++){
            m_segments[i]->print();
            std::cout<<" ";
        }
        std::cout<<"}"<<std::endl;
    }
    std::cout<<std::endl;

}

