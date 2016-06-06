#include "point.h"
#include "segment.h"
#include <iostream>
#include <sstream>

int Point::nb=0;

Point::Point() : Point(0.0, 0.0) {}

Point::Point(float x, float y) :
    m_x(x),
    m_y(y),
//    m_neighbors(),
    m_segments(),
    m_nom("P"),
    m_order(),
    m_index(nb),
    m_generateurs()
{
    m_nom += std::to_string(nb++);
}

Point::Point(Point* p1, Point* p2) :
    Point()
{
    //std::cout<<"Construction du barycentre de "<<p1->getCoord()<<" et "<<p2->getCoord()<<std::endl;
    float x=0, y=0;
    Point* pointC=p1;

    for(int i=0; i<2; ++i)
    {

        //std::cout<<"point: "<<pointC->getNom()<<std::endl;
        if(pointC->isSite())
        {
            //std::cout<<"est un site"<<std::endl;
             m_generateurs.insert(pointC);
             x+=pointC->getX();
             y+=pointC->getY();
        }
        else
            for (std::set<Point*>::iterator it=pointC->m_generateurs.begin(); it!=pointC->m_generateurs.end(); ++it)
            {
                if(this->m_generateurs.insert(*it).second)
                {
                    x+=(*it)->getX();
                    y+=(*it)->getY();
                }
            }
        pointC=p2;
    }
    int n=m_generateurs.size();
    x/=n;
    y/=n;
    m_x=x;
    m_y=y;
    this->print();

}

/*void Point::addNeighbor(Point* p) {
    // add p only if not already present in m_neighbors
    if(std::find(m_neighbors.begin(), m_neighbors.end(), p) == m_neighbors.end()) {
        m_neighbors.push_back(p);
    }
}*/

//il faut ajouter ce point de façon a ce que le tableau soit trier dans l'ordre trigo
void Point::addSegment(Segment* s) {
    //if(std::find(m_segments.begin(), m_segments.end(), s) == m_segments.end()) {
    //    m_segments.push_back(s);}

    if(m_segments.size() == 0) m_segments.push_back(s);
    else {
        std::vector<Segment*>::reverse_iterator it;
        for(it = m_segments.rbegin() ; it != m_segments.rend() && s->isBefore((Segment*)*it) ; ++it);
        if(s != *it) m_segments.insert(it.base(), s);
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

// si les deux point sont egaux?
bool Point::isBefore(Point *p) const {
    return m_x < p->m_x || m_x == p->m_x && m_y < p->m_y;
}

Segment* Point::getSegment(int i) const {
    return m_segments[i];
}

int Point::nbSegments() const {
    std::cout << m_segments.size();
    return m_segments.size();
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

std::string Point::getCoord() const {
    std::ostringstream str;
    str << "(" << std::to_string(m_x) << ";" << std::to_string(m_y) << ")";
    return str.str();
}

void Point::print() const {
    std::cout<<m_nom<<": ("<<this->getX()<<','<<this->getY()<<") ";
    if (m_generateurs.size()>0){
        std::cout<<"generateurs: ( ";
        for (std::set<Point*>::iterator it=m_generateurs.begin(); it!=m_generateurs.end(); ++it)
            std::cout<<(*it)->getNom()<<' ';
        std::cout<<")  ";
    }
    if (m_segments.size()>0){

        std::cout<<"segments sortants: { ";
        for(int i=0; i<m_segments.size(); i++){
            m_segments[i]->print();
            std::cout<<" ";
        }
        std::cout<<"}"<<std::endl;
    }
    else std::cout<<std::endl;
}

int Point::getIndex() const {
    return m_index;
}

bool Point::isSite() const
{
    return m_generateurs.empty();
}

int Point::nbGenerateurs() const
{
    return m_generateurs.size();
}

void Point::initIndex()
{
    nb=0;
}

int Point::getOrder() const {
    return m_order;
}

void Point::setOrder(int order) {
    m_order = order;
}


std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << p.m_nom << " "
        << p.m_x << " "
        << p.m_y;
    return out;
}

std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.m_nom
       >> p.m_x
       >> p.m_y;
    return in;
}
