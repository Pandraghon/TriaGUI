#include "segment.h"
#include <iostream>

int Segment::nb=0;

Segment::Segment(Point *p1, Point *p2)
    : m_nom(), m_order(), m_index(nb)
{
    if(p1->isBefore(p2)) {
        m_points[0] = p1;
        m_points[1] = p2;
        p1->addSegment(this);
    } else {
        m_points[0] = p2;
        m_points[1] = p1;
        p2->addSegment(this);
    }
    m_nom = '['+m_points[0]->getNom()+m_points[1]->getNom()+']';
    nb++;
}

Point* Segment::getP0() const {
    return this->m_points[0];
}

Point* Segment::getP1() const {
    return this->m_points[1];
}

bool Segment::isBefore(Segment* s) const{
    if(this->getP0()->isBefore(s->getP0())) return true;
    else if( this->getP0() == s->getP0() ) return s->getP1()->isLeft(this);
    //else if( this->getP1() == s->getP1() ) return s->getP0()->isLeft(this);
    else return false;
}

std::string Segment::getNom() const{
    return m_nom;
}

void Segment::print() const{
    std::cout<<this->getNom();
            //<<'('<<this->getP0()->getNom()<<')'<<"--------------"
            //<<'('<<this->getP1()->getNom()<<')'
            //<<std::endl;

}

int Segment::getIndex() const {
    return m_index;
}

void Segment::initIndex() {
    nb = 0;
}

int Segment::getOrder() const {
    return m_order;
}

void Segment::setOrder(int order) {
    m_order = order;
}



std::ostream &operator<<(std::ostream &out, const Segment &s) {
    out << s.m_points[0]->getOrder() << " "
        << s.m_points[1]->getOrder();
    return out;
}


std::istream &operator>>(std::istream &in, Segment &s) {
    in >> s.m_nom;
    return in;
}
