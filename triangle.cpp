#include <iostream>
#include "triangle.h"
#include "segment.h"

int Triangle::nb=0;

Triangle::Triangle(Point* p1, Point* p2, Point* p3):
    m_points(),
    m_voisins(),
    m_order(),
    m_index(nb++),
    m_calculated(false)
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

Triangle::Triangle(Point *p1, Point *p2, Point *p3, Data *d)
{
    Segment *s1, *s2, *s3;
    if(!p1->isSegment(p2)) s1=new Segment(p1, p2);
    if(!p1->isSegment(p3)) s2=new Segment(p1, p3);
    if(!p2->isSegment(p3)) s3=new Segment(p2, p3);
}

//s1 et s2 ont le meme point origine
Triangle::Triangle(Segment *s1, Segment *s2, Triangle ***voisins):
    Triangle(s1->getP0(), s1->getP1(), s2->getP1())
{
    //m_calculated=true;

    Point *p=s1->getP0(), *q=s1->getP1(), *r=s2->getP1(); //s1=[pq] s2=[pr]
    std::cout<<m_nom<<std::endl;

    if(r->isLeft(s1))//ce triangle est a gauche de s1 et a droite de s2
    //verifier si il y'a un triangle a droite de s1 ou a gauche de s2
    {
        voisins[p->getIndex()][q->getIndex()]=this; //a gauche de s1=[pq]
    //std::cout<<" est a gauche de "<<s1->getNom()<<" mis en ["<<p->getIndex()<<"]["<<q->getIndex()<<"]"<<std::endl;
        voisins[r->getIndex()][p->getIndex()]=this; //a droite de s2=[pr]
    //std::cout<<" est a droite de "<<s2->getNom()<<" mis en ["<<r->getIndex()<<"]["<<p->getIndex()<<"]"<<std::endl;

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

///CE CAS NE SE PRESENTE JAMAIS CAR LES SEGMENTS SORTANTS D'UN POINT SONT TRIEES DANS LE SENS TRIGO
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
    //std::cout<<" est a gauche de ["<<q->getNom()<<r->getNom()<<"] mis en ["<<q->getIndex()<<"]["<<r->getIndex()<<"]"<<std::endl;
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

std::vector<Segment *> Triangle::getSegments() {
    Point *p1=this->getP0(),
    *p2=this->getP1(),
    *p3=this->getP2();

     Segment *seg1, *seg2, *seg3;

    //recherche des segments formant ce triangle
    int s=0;

    while(p1->getSegment(s)->getP1()!=p2) ++s;
    seg1=p1->getSegment(s);

    s=0;
    while(p1->getSegment(s)->getP1()!=p3) ++s;
    seg2=p1->getSegment(s);

    s=0;
    while(p2->getSegment(s)->getP1()!=p3) ++s;
    seg3=p2->getSegment(s);

    std::vector<Segment*> segs;
    segs.push_back(seg1);segs.push_back(seg2);segs.push_back(seg3);
    return segs;
}

void Triangle::getVoisinsHachure(std::vector<bool> &marque, std::vector<Triangle *> &voisHach)
{
    if(marque[this->getIndex()]) return;
    if(!this->calculated()){
        marque[this->getIndex()]=true;
        return;
    }
    //hachuré pas traité
    voisHach.push_back(this);
    marque[this->getIndex()]=true;
    for(int i=0; i<3; ++i){
        if(m_voisins[i]!=NULL){
            m_voisins[i]->getVoisinsHachure(marque,voisHach);
        }
    }
}

bool Triangle::marquerVoisinage(Triangle ***voisins)
{
    this->print();
    Point* p= this->getP0(), *q=this->getP1(), *r=this->getP2();
    if (p->isLeft(q,r))
    {
        voisins[q->getIndex()][r->getIndex()]=this; //a gauche de [qr]
    //std::cout<<" est a gauche de ["<<q->getNom()<<r->getNom()<<"] mis en ["<<q->getIndex()<<"]["<<r->getIndex()<<"]"<<std::endl;
    }
    else
        {
            voisins[r->getIndex()][q->getIndex()]=this;
        //std::cout<<" est a droite de ["<<q->getNom()<<r->getNom()<<"] mis en ["<<r->getIndex()<<"]["<<q->getIndex()<<"]"<<std::endl;
        }

    if (q->isLeft(p,r))
    {
        voisins[p->getIndex()][r->getIndex()]=this; //a gauche de [pr]
    //std::cout<<" est a gauche de ["<<p->getNom()<<r->getNom()<<"] mis en ["<<p->getIndex()<<"]["<<r->getIndex()<<"]"<<std::endl;
    }
    else
    {
            voisins[r->getIndex()][p->getIndex()]=this;
        //std::cout<<" est a droite de ["<<p->getNom()<<r->getNom()<<"] mis en ["<<r->getIndex()<<"]["<<p->getIndex()<<"]"<<std::endl;
    }

    if (r->isLeft(p,q))
    {
        voisins[p->getIndex()][q->getIndex()]=this; //a gauche de [pq]
    //std::cout<<" est a gauche de ["<<p->getNom()<<q->getNom()<<"] mis en ["<<p->getIndex()<<"]["<<q->getIndex()<<"]"<<std::endl;
    }
    else
    {
            voisins[q->getIndex()][p->getIndex()]=this;
        //std::cout<<" est a droite de ["<<p->getNom()<<q->getNom()<<"] mis en ["<<p->getIndex()<<"]["<<q->getIndex()<<"]"<<std::endl;
    }

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


int Triangle::getIndex() const {
    return m_index;
}

bool Triangle::calculated() const
{
    return m_calculated;
}

void Triangle::isCalculated()
{
    m_calculated=true;
}

void Triangle::print() const {
    std::cout<<m_nom;
    if(calculated()) std::cout<<" hachuré ";
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

void Triangle::initIndex() {
    nb = 0;
}

int Triangle::getOrder() const {
    return m_order;
}

void Triangle::setOrder(int order) {
    m_order = order;
}


std::ostream &operator<<(std::ostream &out, const Triangle &t) {
    out << t.m_nom;
    for(int i{} ; i < 3 ; ++i) {
        out << " ";
        if(t.m_points[i] == NULL) out << "-1";
        else                      out << t.m_points[i]->getOrder();
    }
    for(int i{} ; i < 3 ; ++i) {
        out << " ";
        if(t.m_voisins[i] == NULL) out << "-1";
        else                       out << t.m_voisins[i]->getOrder();
    }
}


std::istream &operator>>(std::istream &in, Triangle &t) {
    in >> t.m_nom;
    for(int i{} ; i < 3 ; ++i) {
        int p;
        in >> p;
        if(p == -1) t.m_points[i] = NULL;
        //else        t.m_points[i] = lkvl;
    }
    for(int i{} ; i < 3 ; ++i) {
        int v;
        in >> v;
        if(v == -1) t.m_voisins[i] = NULL;
        //else        t.m_voisins[i] = l,lk;
    }
    return in;
}
