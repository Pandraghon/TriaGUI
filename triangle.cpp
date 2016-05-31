#include <iostream>
#include "triangle.h"
#include "segment.h"

int Triangle::nb=0;

Triangle::Triangle(Point* p1, Point* p2, Point* p3):
    m_points(),
    m_voisins()
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
    for(int i=0; i<3; ++i) m_voisins[i]=NULL;
    m_nom=m_points[0]->getNom()+m_points[1]->getNom()+m_points[2]->getNom();
}

//s1 et s2 ont le meme point origine
Triangle::Triangle(Segment *s1, Segment *s2, Triangle ***voisins):
    Triangle(s1->getP0(), s1->getP1(), s2->getP1())
{
    Point *p=s1->getP0(), *q=s1->getP1(), *r=s2->getP1(); //s1=[pq] s2=[pr]
    std::cout<<m_nom<<std::endl;

    if(r->isLeft(s1))//ce triangle est a gauche de s1 et a droite de s2
    //verifier si il y'a un triangle a droite de s1 ou a gauche de s2
    {
        voisins[p->getIndex()][q->getIndex()]=this; //a gauche de s1=[pq]
    std::cout<<std::endl<<" est a gauche de "<<s1->getNom()<<" mis en ["<<p->getIndex()<<"]["<<q->getIndex()<<"]"<<std::endl;
        voisins[r->getIndex()][p->getIndex()]=this; //a droite de s2=[pr]
    std::cout<<" est a droite de "<<s2->getNom()<<" mis en ["<<r->getIndex()<<"]["<<p->getIndex()<<"]"<<std::endl;

        if( voisins[q->getIndex()][p->getIndex()]!=NULL)//si il y'a un triangle a droite de s1
        {
            int pos = this->pos3emePoint(s1);
            this->setVoisin(pos,voisins[q->getIndex()][p->getIndex()]);
//            std::cout<<"Le "<<pos<<"eme voisin est "<<voisins[q->getIndex()][p->getIndex()]->getNom()<<std::endl;

            pos=voisins[q->getIndex()][p->getIndex()]->pos3emePoint(s1);
            voisins[q->getIndex()][p->getIndex()]->setVoisin(pos,this);
//            std::cout<<"est le "<<pos<<"eme voisin de "<<voisins[q->getIndex()][p->getIndex()]->getNom()<<std::endl;
        }
        if( voisins[p->getIndex()][r->getIndex()]!=NULL)//si il y'a un triangle a gauche de s2
        {
            int pos = this->pos3emePoint(s2);
            this->setVoisin(pos,voisins[p->getIndex()][r->getIndex()]);
//            std::cout<<"Le "<<pos<<"eme voisin est "<<voisins[p->getIndex()][r->getIndex()]->getNom()<<std::endl;

            pos=voisins[p->getIndex()][r->getIndex()]->pos3emePoint(s2);
            voisins[p->getIndex()][r->getIndex()]->setVoisin(pos,this);
//            std::cout<<"est le "<<pos<<"eme voisin de "<<voisins[p->getIndex()][r->getIndex()]->getNom()<<std::endl;
        }
    }

///CE CAS NE SE PRESENTE JAMAIS CAR LES SEGMENTS D'UN POINT SONT TRIEES DANS LE SENS TRIGO
//    else //le triangle est a droite de s1=[pq] et a gauche de s2=[pr] TO DO : verifier si il y'a un triangle a droite de s2 ou a gauche de s1
//    {
//        voisins[q->getIndex()][p->getIndex()]=this;
//    std::cout<<std::endl<<" est a droite de "<<s1->getNom()<<" mis en ["<<q->getIndex()<<"]["<<p->getIndex()<<"]"<<std::endl;
//        voisins[p->getIndex()][r->getIndex()]=this;
//    std::cout<<" est a gauche de "<<s2->getNom()<<" mis en ["<<p->getIndex()<<"]["<<r->getIndex()<<"]"<<std::endl;
//    }
///FIN DU CAS

    if (p->isLeft(q,r))
    {
        voisins[q->getIndex()][r->getIndex()]=this; //a gauche de [qr]
    std::cout<<" est a gauche de ["<<q->getNom()<<r->getNom()<<"] mis en ["<<q->getIndex()<<"]["<<r->getIndex()<<"]"<<std::endl;
        if( voisins[r->getIndex()][q->getIndex()]!=NULL)//si il y'a un triangle a droite de [qr]
        {
            int pos = this->pos3emePoint(q,r);
            this->setVoisin(pos,voisins[r->getIndex()][q->getIndex()]);
//            std::cout<<"Le "<<pos<<"eme voisin est "<<voisins[q->getIndex()][p->getIndex()]->getNom()<<std::endl;

            pos=voisins[r->getIndex()][q->getIndex()]->pos3emePoint(q,r);
            voisins[r->getIndex()][q->getIndex()]->setVoisin(pos,this);
//            std::cout<<"est le "<<pos<<"eme voisin de "<<voisins[q->getIndex()][p->getIndex()]->getNom()<<std::endl;
        }
    }
///CE CAS NE SE PRESENTE JAMAIS CAR LES SEGMENTS D'UN POINT SONT TRIEES DANS LE SENS TRIGO
//    else
//    {
//        voisins[r->getIndex()][q->getIndex()]=this;
//    std::cout<<" est a droite de ["<<q->getNom()<<r->getNom()<<"] mis en ["<<r->getIndex()<<"]["<<q->getIndex()<<"]"<<std::endl;
//    }
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

Point *Triangle::getP(int i) const {
    return m_points[i];
}

void Triangle::setVoisin(int i, Triangle *t) {
    m_voisins[i]=t;
}

Triangle *Triangle::getVoisin(int i) const {
    return m_voisins[i];
}

std::string Triangle::getNom() const {
    return m_nom;
}

//les points du triangle sont triées les points du segment aussi
int Triangle::pos3emePoint(Segment *s) {
    if(s->getP0()==this->getP0()){
        if(s->getP1()==this->getP1()) return 2;
        else return 1;
    }
    else return 0;
}

int Triangle::pos3emePoint(Point *p1, Point *p2) {
    for(int i=0; i<3; i++){
        if(!(this->getP(i)==p1 || this->getP(i)==p2)) return i;
    }
}

void Triangle::print() const {
    std::cout<<m_nom;
    if(m_voisins[0]!=NULL||m_voisins[1]!=NULL||m_voisins[2]!=NULL)
    {
        std::cout<<"   Ses Voisins: ";
        for(int v=0; v<3; ++v){
            if(m_voisins[v]!=NULL)
                std::cout<<v<<" : "<<this->getVoisin(v)->getNom()<<"   ";
        }
        std::cout<<std::endl;
    }
}
