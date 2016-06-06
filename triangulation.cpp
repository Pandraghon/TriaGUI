#include "triangulation.h"
#include <iostream>

#include "data.h"

Triangulation::Triangulation() :
    m_points(),
    m_segments(),
    m_triangles(),
    m_ordre(1)
{}

Triangulation::Triangulation(Data* d) :
    Triangulation()
{

    //addPoint(new Point());
    int ordre=d->nbTriangulation();
    //la triangulation d'ordre n est a la case n-1
    //if (ordre==1)
    {
        m_ordre=d->getTriangulation(ordre-1)->getOrdre()+1;
        //std::vector<Point*> points = d->getTriangulation(ordre-1)->getPoints();
        std::cout<<"TRIANGULATION D ORDRE "<<this->getOrdre()<<":"<<std::endl;
        std::vector<Triangle*> triangles = d->getTriangulation(ordre-1)->getTriangles();
        int nbSeg=d->getTriangulation(ordre-1)->getSegments().size();
        this->initVoisins(nbSeg);
        Point::initIndex();
        Segment::initIndex();
        Triangle::initIndex();
        this->calculNextOrdrePoints(triangles, nbSeg);
        /*this->addSegment(new Segment(this->getPoint(0), this->getPoint(1)));
        this->addSegment(new Segment(this->getPoint(3), this->getPoint(4)));
        this->addSegment(new Segment(this->getPoint(1), this->getPoint(5)));
        this->addSegment(new Segment(this->getPoint(1), this->getPoint(6)));
        this->addSegment(new Segment(this->getPoint(3), this->getPoint(7)));
        this->addSegment(new Segment(this->getPoint(7), this->getPoint(8)));*/
        this->print();
        this->scanTriangles();
        d->addTriangulation(this);
        std::cout<<std::endl;
        this->print();
    }
//    for(int i=0; i<m_points.size(); ++i){
//        delete[] voisins[i];
//    }
//    delete[] voisins;

}

void Triangulation::initVoisins(int nbPoints)
{
    //int nbPoints=m_points.size();
    voisins = new Triangle**[nbPoints];
    for(int i=0; i<nbPoints; ++i){
        voisins[i] = new Triangle*[nbPoints];
        for(int j=0; j<nbPoints; ++j)
            voisins[i][j]=NULL;
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

Triangle *Triangulation::getTriangle(int i) const {
    return m_triangles.at(i);
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
    if (m_ordre==1)
        initVoisins(nbPoints);
   std::cout << std::endl <<"Scannig triangles" << std::endl;
//pour chaque point
   for(int p=0; p<nbPoints; ++p)
   {
       pointCourant=m_points[p];
       int nbSeg=pointCourant->nbSegments();
  //     std::cout<<"Point courant: "<<pointCourant->getNom()<<" "<<nbSeg<<" segments sortants"<<std::endl;
       if(nbSeg>1){
           for(int s=0; s<nbSeg-1; ++s)
           {
   //            std::cout<<"Segment "<<s<<" : "<<pointCourant->getSegment(s)->getNom()<<std::endl;
               if( pointCourant->getSegment(s)->getP1()->isSegment( pointCourant->getSegment(s+1)->getP1()) )
               {
   //                std::cout<<"Relier a: "<<pointCourant->getSegment(s+1)->getNom()<<std::endl<<std::endl<<"Triangle ";
                   //si il aucun triangle n'a été construit a gauche du premier seg
                   if(voisins[pointCourant->getSegment(s)->getP0()->getIndex()][pointCourant->getSegment(s)->getP1()->getIndex()]==NULL)
                   {
                       Triangle *t = new Triangle(pointCourant->getSegment(s), pointCourant->getSegment(s+1), voisins);
                       //mettre ce triangle dans trois position dans la matrice pour renseigner sa position par rapport au trois segment qui le constitue
                       this->addTriangle(t);
    //                   std::cout<<std::endl;
                   }

               }
           }
       }
   }
//   for(int i=0; i<nbPoints; ++i){
//       delete[] voisins[i];
//   }
//   delete[] voisins;

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

void Triangulation::calculNextOrdrePoints(std::vector<Triangle *> triangles, int nbSegments)
{
    int nbTriangles=triangles.size();
//    int nbSegments=segments.size();
    Triangle *triangleCourant;
    Segment *seg1, *seg2, *seg3;
    Point *p1, *p2, *p3;
    Point *m1, *m2, *m3;
//    std::vector<Point*> gene(2,NULL);
    std::vector<bool> tri(nbTriangles,false);
    std::vector<Point*> bary(nbSegments,NULL);
//    std::cout<<"nbTriangles "<<nbTriangles<<std::endl;
    for (int t=0; t<nbTriangles; ++t)
    {
        triangleCourant=triangles[t];

        p1=triangleCourant->getP0();
        p2=triangleCourant->getP1();
        p3=triangleCourant->getP2();
        std::vector<Segment*> segs=triangleCourant->getSegments();
        seg1=segs[0];
        seg2=segs[1];
        seg3=segs[2];

        //recherche des segments formant ce triangle
//        int s=0;
//        std::cout<<"Triangle "<<t<<" :"<<triangleCourant->getNom()<<std::endl;
//        while(p1->getSegment(s)->getP1()!=p2) ++s;
//        seg1=p1->getSegment(s);

//        s=0;
//        while(p1->getSegment(s)->getP1()!=p3) ++s;
//        seg2=p1->getSegment(s);

//        s=0;
//        while(p2->getSegment(s)->getP1()!=p3) ++s;
//        seg3=p2->getSegment(s);

//        triangleCourant->getSegments(seg1, seg2, seg3);
        int i1=seg1->getIndex();
        int i2=seg2->getIndex();
        int i3=seg3->getIndex();
        std::vector<bool> marque(nbTriangles,false);

        if( triangleCourant->calculated() ){
        //Tout les segements des triangles hachurés et de leurs voisins(à faire) génére le m^eme barycentre
            if( bary[i1]==NULL && bary[i2]==NULL && bary[i3]==NULL )
            {
                m1 = new Point(p1, p2);
                bary[i1]=bary[i2]=bary[i3]=m1;
            }
            else
            {
                if(bary[i1]!=NULL) m1=bary[i1];
                if(bary[i2]!=NULL) m1=bary[i2];
                if(bary[i3]!=NULL) m1=bary[i3];
                bary[i1]=bary[i2]=bary[i3]=m1;
            }
            // marquer le bary des voisins aussi
//A TESTER
            std::vector<Triangle*> voisHach;
            triangleCourant->getVoisinsHachure(marque, voisHach);
            for (int i=0; i<voisHach.size() ;i++){
                std::vector<Segment*> segs=voisHach[i]->getSegments();
                for (int j=0; j<segs.size(); ++j){
                    bary[segs[j]->getIndex()]=m1;
                }

            }


        }
        else
        {
            if(bary[i1]==NULL){
                m1 = new Point(p1, p2);
                bary[i1]=m1;
            }
            else m1=bary[i1];
            std::cout<<"seg 1: "<<seg1->getNom()<<"  ";
            std::cout<<"barycentre "<<m1->getNom()<<std::endl;


            if(bary[i2]==NULL){
                m2 = new Point(p1, p3);
                bary[i2]=m2;
            }
            else m2=bary[i2];
            std::cout<<"seg 2: "<<seg2->getNom()<<"  ";
            std::cout<<"son barycentre "<<m2->getNom()<<std::endl;


            if(bary[i3]==NULL){
                m3 = new Point(p2, p3);
                bary[i3]=m3;
            }
            else m3=bary[i3];
            std::cout<<"seg 3: "<<seg3->getNom()<<"  ";
            std::cout<<"son barycentre "<<m3->getNom()<<std::endl;

            Segment *m12 = new Segment(m1, m2);
            Segment *m13 = new Segment(m1, m3);
            Segment *m23 = new Segment(m3, m2);
            Triangle *tr = new Triangle(m1, m2, m3);
            tr->isCalculated();
            std::cout<<"Segments crees "<<m12->getNom()<<" "<<m13->getNom()<<" "<<m23->getNom()<<std::endl;
            Point* p[]= {m1, m2, m3};
            this->addPoints(p, 3);
            Segment* seg[]={m12, m13, m23};
            this->addSegments(seg, 3);
            this->addTriangle(tr);
            tr->marquerVoisinage(this->voisins);
            tri[triangleCourant->getIndex()]=true;
        }


    }

}

void Triangulation::clear() {
    for(unsigned int j{} ; j < m_points.size() ; ++j) delete[] voisins[j];
    for(unsigned int j{} ; j < m_points.size() ; ++j) delete m_points[j];
    for(unsigned int j{} ; j < m_segments.size() ; ++j) delete m_segments[j];
    for(unsigned int j{} ; j < m_triangles.size() ; ++j) delete m_triangles[j];
    delete[] voisins;
    m_points.clear();
    m_segments.clear();
    m_triangles.clear();
}

/*void Triangulation::calculMilieux(std::vector<Point *> points) {
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
}*/

/*void Triangulation::mileuxSegmentsTriangles(std::vector<Triangle *> triangles, int nbSegments) {
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
}*/

std::ostream& operator<<(std::ostream& out, const Triangulation& t) {
    out << t.m_points.size() << std::endl;
    for(unsigned int i{} ; i < t.m_points.size() ; ++i) {
        Point* p = t.m_points.at(i);
        p->setOrder(i);
        out << *p << std::endl;
    }
    out << t.m_segments.size() << std::endl;
    for(unsigned int i{} ; i < t.m_segments.size() ; ++i) {
        Segment* s = t.m_segments.at(i);
        s->setOrder(i);
        out << *s << std::endl;
    }
    out << t.m_triangles.size() << std::endl;
    for(unsigned int i{} ; i < t.m_triangles.size() ; ++i) {
        Triangle* r = t.m_triangles.at(i);
        r->setOrder(i);
        out << *r << std::endl;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Triangulation* t) {
    int ptSize, segSize, triSize;
    in >> ptSize;
    t->m_points.resize(ptSize);
    for(unsigned int i{} ; i < ptSize ; ++i) {
        t->m_points[i];
    }
    return in;
}
