#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdlib.h>
#include "point.h"


class Triangle
{
public:
    Triangle(Point* p1, Point* p2, Point* p3);
    Point* getP0() const;
    Point* getP1() const;
    Point* getP2() const;
    void setVoisin(int i, Triangle* t);
    Triangle* getVoisin(int i);
    std::string getNom() const;
    void print() const;

private:
    Point* m_points[3];
    Triangle* m_voisins[3];
    std::string m_nom;
    static int nb;
};

#endif // TRIANGLE_H
