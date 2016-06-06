#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdlib.h>
#include "point.h"
#include "data.h"

class Data;

class Triangle
{
public:
    Triangle(Point* p1, Point* p2, Point* p3);
    Triangle(Point* p1, Point* p2, Point* p3, Data* d);
    Triangle(Segment *s1, Segment *s2, Triangle*** voisins);
    Point* getP0() const;
    Point* getP1() const;
    Point* getP2() const;
    Point* getP(int i) const;
    std::vector<Segment*> getSegments();
    void getVoisinsHachure(std::vector<bool> &marque, std::vector<Triangle *> &voisHach);
    bool marquerVoisinage(Triangle*** voisins);
    void setVoisin(int i, Triangle* t);
    Triangle* getVoisin(int i) const;
    std::string getNom() const;
    int pos3emePoint(Segment *s);
    int pos3emePoint(Point* p1, Point* p2);
    int getIndex() const;
    bool calculated() const;
    void isCalculated();
    void print() const;
    static void initIndex();

    friend std::ostream& operator<<(std::ostream&, const Triangle&);
    friend std::istream& operator>>(std::istream&, Triangle&);

    int getOrder() const;
    void setOrder(int order);

private:
    Point* m_points[3];
    Triangle* m_voisins[3];
    std::string m_nom;
    int m_order;
    int m_index;
    static int nb;
    bool m_calculated; // generé automatiquement
};

std::ostream& operator<<(std::ostream& out, const Triangle& t);
std::istream& operator>>(std::istream& in, Triangle& t);

#endif // TRIANGLE_H
