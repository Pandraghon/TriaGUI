#include "triangulation.h"
#include <iostream>

#include "data.h"

Triangulation::Triangulation() :
    m_points(),
    m_segments(),
    m_ordre(1)
{}

Triangulation::Triangulation(Data* d) :
    Triangulation()
{
    int ordre=d->nbTriangulation();
    //la triangulation d'ordre o est a la case o-1
    if (ordre==1)
    {
        m_ordre=2;
        //std::vector<Point*> points = d->getTriangulation(ordre-1)->getPoints();
        std::vector<Triangle*> triangles = d->getTriangulation(ordre-1)->getTriangles();
        //this->calculMilieux(points);
        int nbSeg=d->getTriangulation(ordre-1)->getSegments().size();
        this->mileuxSegmentsTriangles(triangles, nbSeg);
        d->addTriangulation(this);
        std::cout<<std::endl;
        this->print();
    }
}

int Triangulation::getOrdre() const {
    return m_ordre;
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

Segment* Triangulation::getSegment(Point *p, Point *q) const {
    Point *p0, *p1;
    if(p->isBefore(q)) {p0=p; p1=q;}
    else {p0=q; p1=p;}
    int nbSeg = p0->nbSegments();
    if(nbSeg>1){
        for(int s=0; s<nbSeg; ++s)
        { if(p0->getSegment(s)->getP1()==p1)
                return p0->getSegment(s);
        }
    }
    return NULL;
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

void Triangulation::addTriangle(Triangle *t) {
    m_triangles.push_back(t);
}

std::vector<Triangle *> Triangulation::getTriangles() const {
    return m_triangles;
}

void Triangulation::print() const {
    std::cout<<"Triangulation d'ordre "<<this->getOrdre()<<":"<<std::endl;
    std::cout<<"Points: "<<m_points.size()<<std::endl;
    for(int i=0; i<m_points.size(); i++){
        m_points[i]->print();
    }
    std::cout<<"Segments: "<<m_segments.size()<<std::endl;
    for(int i=0; i<m_segments.size(); i++){
        m_segments[i]->print();
        std::cout<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Triangles: "<<m_triangles.size()<<std::endl;
    for(int i=0; i<m_triangles.size(); i++){
        m_triangles[i]->print();
        std::cout<<" ";
    }
    std::cout<<std::endl;
}

void Triangulation::scanTriangles() {
    int nbPoints=m_points.size();
   Point *pointCourant;
   Segment *segCourant;
   Triangle ***voisins = new Triangle**[nbPoints];
   for(int i=0; i<nbPoints; ++i){
       voisins[i] = new Triangle*[nbPoints];
       for(int j=0; j<nbPoints; ++j)
           voisins[i][j]=NULL;
   }
//pour chaque point
   for(int p=0; p<nbPoints; ++p)
   {
       pointCourant=m_points[p];
       int nbSeg=pointCourant->nbSegments();
       std::cout<<"Point courant: "<<pointCourant->getNom()<<" nb segments:"<<nbSeg<<std::endl;
       if(nbSeg>1){
           for(int s=0; s<nbSeg-1; ++s)
           {
               std::cout<<"  Segment courant: "<<pointCourant->getSegment(s)->getNom()<<std::endl;
               if( pointCourant->getSegment(s)->getP1()->isSegment( pointCourant->getSegment(s+1)->getP1()) )
               {
                   std::cout<<"     Relier a: "<<pointCourant->getSegment(s+1)->getNom()<<std::endl<<"Triangle :) ";
                   Triangle *t = new Triangle(pointCourant->getSegment(s), pointCourant->getSegment(s+1), voisins);
                   //mettre ce triangle dans trois position dans la matrice pour renseigner sa position par rapport au trois segment qui le constitue
                   this->addTriangle(t);
                   std::cout<<t->getNom()<<std::endl;
               }
           }
       }
   }

   //pour chaque segment
   //std::cout << m_segments.size() << " segments" << std::endl;

/*    for(int s=0; s<this->m_segments.size(); s++){
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
*/
}

void Triangulation::calculMilieux(std::vector<Point *> points) {
    int nbPoints=points.size();
    Point *pointCourant;
    Segment *segCourant;
    for(int p=0; p<nbPoints; ++p)
    {
        pointCourant=points[p];
        int nbSeg=pointCourant->nbSegments();
        if(nbSeg>0){
            for(int s=0; s<nbSeg; ++s){
                segCourant = pointCourant->getSegment(s);
                Point *milieu = new Point((segCourant->getP0()->getX()+segCourant->getP1()->getX())/2,(segCourant->getP0()->getY()+segCourant->getP1()->getY())/2);
                this->addPoint(milieu);
            }
        }
    }
}

void Triangulation::mileuxSegmentsTriangles(std::vector<Triangle *> triangles, int nbSegments) {
    int nbTriangles=triangles.size();
//    int nbSegments=segments.size();
    Triangle *triangleCourant;
    Segment *seg1, *seg2, *seg3;
    Point *p1, *p2, *p3;
    Point *m1, *m2, *m3;

    std::vector<Point*> milieux(nbSegments,NULL);
//    std::cout<<"nbTriangles "<<nbTriangles<<std::endl;
    for (int t=0; t<nbTriangles; ++t)
    {
        triangleCourant=triangles[t];
        p1=triangleCourant->getP0();
        p2=triangleCourant->getP1();
        p3=triangleCourant->getP2();

        //recherche des segments formant ce triangle
        int s=0;
        std::cout<<"Triangle "<<t<<" :"<<triangleCourant->getNom()<<std::endl;
        while(p1->getSegment(s)->getP1()!=p2) ++s;
        seg1=p1->getSegment(s);
        std::cout<<"seg 1: "<<seg1->getNom()<<std::endl;
        int i1=seg1->getIndex();
        if(milieux[i1]==NULL){
            m1 = new Point((seg1->getP0()->getX()+seg1->getP1()->getX())/2,(seg1->getP0()->getY()+seg1->getP1()->getY())/2);
            milieux[i1]=m1;
        }
        else m1=milieux[i1];
        std::cout<<"son milieu "<<m1->getNom()<<std::endl;

        s=0;
        while(p1->getSegment(s)->getP1()!=p3) ++s;
        seg2=p1->getSegment(s);
        std::cout<<"seg 2: "<<seg2->getNom()<<std::endl;

        int i2=seg2->getIndex();
        if(milieux[i2]==NULL){
            m2 = new Point((seg2->getP0()->getX()+seg2->getP1()->getX())/2,(seg2->getP0()->getY()+seg2->getP1()->getY())/2);
            milieux[i2]=m2;
        }
        else m2=milieux[i2];
        std::cout<<"son milieu "<<m2->getNom()<<std::endl;

        s=0;
        while(p2->getSegment(s)->getP1()!=p3) ++s;
        seg3=p2->getSegment(s);
        std::cout<<"seg 3: "<<seg3->getNom()<<std::endl;
        int i3=seg3->getIndex();
        if(milieux[i3]==NULL){
            m3 = new Point((seg3->getP0()->getX()+seg3->getP1()->getX())/2,(seg3->getP0()->getY()+seg3->getP1()->getY())/2);
            milieux[i3]=m3;
        }
        else m3=milieux[i3];
        std::cout<<"son milieu "<<m3->getNom()<<std::endl;

        Segment *m12 = new Segment(m1, m2);
        Segment *m13 = new Segment(m1, m3);
        Segment *m23 = new Segment(m3, m2);
        Triangle *tr = new Triangle(m1, m2, m3);
        Point* p[]= {m1, m2, m3};
        this->addPoints(p, 3);
        Segment* seg[]={m12, m13, m23};
        this->addSegments(seg, 3);
        this->addTriangle(tr);

    }
}

std::ostream& operator<<(std::ostream& out, const Triangulation& t) {
    out << t.m_points.size() << std::endl;
    for(Point* p : t.m_points)
        out << *p << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Triangulation& t) {
    return in;
}
