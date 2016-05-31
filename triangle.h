#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdlib.h>
#include "point.h"


class Triangle
{
public:
    Triangle(Point* p1, Point* p2, Point* p3);
    Triangle(Segment *s1, Segment *s2, Triangle*** voisins);
    Point* getP0() const;
    Point* getP1() const;
    Point* getP2() const;
    Point* getP(int i) const;
    void setVoisin(int i, Triangle* t);
    Triangle* getVoisin(int i) const;
    std::string getNom() const;
    int pos3emePoint(Segment *s);
    int pos3emePoint(Point* p1, Point* p2);

    void print() const;

    friend std::ostream& operator<<(std::ostream&, const Triangle&);
    friend std::istream& operator>>(std::istream&, Triangle&);

private:
    Point* m_points[3];
    Triangle* m_voisins[3];
    std::string m_nom;
    static int nb;
};

std::ostream& operator<<(std::ostream& out, const Triangle& t);
std::istream& operator>>(std::istream& in, Triangle& t);

#endif // TRIANGLE_H
