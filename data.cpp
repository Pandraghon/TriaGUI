#include "data.h"
#include "simple_svg_1.0.0.hpp"
#include "graphicsscene.h"
#include <QColor>

Data::Data() :
    m_triangs(1, new Triangulation())
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
    clear();
}

std::vector<Triangulation*> Data::getTriangulations() const {
    return m_triangs;
}

Triangulation *Data::getTriangulation(int index) const {
    return m_triangs.at(index);
}

unsigned int Data::nbTriangulation() const {
    return m_triangs.size();
}

void Data::addTriangulation(Triangulation *t) {
    this->m_triangs.push_back(t);
}

void Data::nextOrder() {
    m_triangs.push_back(new Triangulation(this));
}

void Data::exportToEPS(const std::string &filename) {
    Triangle* t = m_triangs[0]->getTriangles()[0];

    double xmin(t->getP0()->getX()), ymin(t->getP0()->getY()),
           xmax(xmin), ymax(ymin);

    std::vector<svg::Polygon> poly;

    for(unsigned int i{} ; i < m_triangs.size() ; ++i) {
        for(auto t : m_triangs[i]->getTriangles()) {
            QColor col = GraphicsScene::color(i);
            svg::Polygon p(svg::Color(col.red(), col.green(), col.blue()), svg::Stroke(.1, svg::Color(col.red() / 1.5, col.green() / 1.5, col.blue() / 1.5)));
            for(int j{} ; j < 3 ; ++j) {
                Point* n = t->getP(j);
                if(n->getX() > xmax) xmax = n->getX();
                else if(n->getX() < xmin) xmin = n->getX();
                if(n->getY() > ymax) ymax = n->getY();
                else if(n->getY() < ymin) ymin = n->getY();
                p << svg::Point(n->getX(), n->getY());
                std::cout << n->getX() << n->getY() << std::endl;
            }
            poly.push_back(p);
        }
    }


    svg::Dimensions dim(xmax - xmin, ymax - ymin);
    svg::Document doc(filename, svg::Layout(dim, svg::Layout::BottomLeft, 1, svg::Point(-xmin, -ymin)));
    for(auto p : poly) doc << p;
    doc.save();
}

void Data::clear() {
    for(unsigned int i{} ; i < m_triangs.size() ; ++i) delete m_triangs[i];
    m_triangs.clear();
    Point::initIndex();
    Segment::initIndex();
    Triangle::initIndex();
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
    int triangsSize{};
    in >> triangsSize;
    v.m_triangs.resize(triangsSize);
    Triangulation t;
    for(int i{} ; i < triangsSize ; ++i) {
        in >> t;
        v.m_triangs[i] = new Triangulation(t);
        Point::initIndex();
        Segment::initIndex();
        Triangle::initIndex();
    }
//    int s;
//    in >> s;
//    Point *p;
//    for(int i = 0 ; i < s ; ++i) in >> p;
//    p->print();
    return in;
}
