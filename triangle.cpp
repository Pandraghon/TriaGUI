#include <iostream>
#include "triangle.h"

int Triangle::nb=0;

Triangle::Triangle(Point* p1, Point* p2, Point* p3):
    m_points(),
    m_nom('t' + std::to_string(nb))
{
    if(p1->isBefore(p2)) {
        if(p3->isBefore(p1)) {
        m_points[0] = p3;
        m_points[1] = p1;
        m_points[2] = p2;
        }
        else {
            if(p3->isBefore(p2)){
                m_points[0] = p1;
                m_points[1] = p3;
                m_points[2] = p2;
            }
            else{
                m_points[0] = p1;
                m_points[1] = p2;
                m_points[2] = p3;
            }
        }
    }
    else {
        if(p3->isBefore(p2)) {
        m_points[0] = p3;
        m_points[1] = p2;
        m_points[2] = p1;
        }
        else {
            if(p3->isBefore(p1)){
                m_points[0] = p2;
                m_points[1] = p3;
                m_points[2] = p1;
            }
            else{
                m_points[0] = p2;
                m_points[1] = p1;
                m_points[2] = p3;
            }
        }

    }

}

Point* Triangle::getP0() const{
    return m_points[0];
}

Point* Triangle::getP1() const{
    return m_points[1];
}

Point* Triangle::getP2() const{
    return m_points[2];
}

void Triangle::setVoisin(int i, Triangle *t)
{
    m_voisins[i]=t;
}

Triangle *Triangle::getVoisin(int i)
{
    return m_voisins[i];
}

std::string Triangle::getNom() const{
    return m_nom;
}

void Triangle::print() const{
    std::string nom = m_points[0]->getNom()+m_points[1]->getNom()+m_points[2]->getNom();
    std::cout<<nom;
}
