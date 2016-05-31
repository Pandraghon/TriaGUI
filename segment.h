#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

class Segment
{
public:
    Segment(Point* p1, Point* p2);
    bool isBefore(Segment* s) const;
    Point* getP0() const;
    Point* getP1() const;
    std::string getNom() const;
    void print() const;
    int getIndex() const;

    friend std::ostream& operator<<(std::ostream&, const Segment&);
    friend std::istream& operator>>(std::istream&, Segment&);

private:
    static int nb;
    Point* m_points[2];
    std::string m_nom;
    int m_index;
};

std::ostream& operator<<(std::ostream& out, const Segment& p);
std::istream& operator>>(std::istream& in, Segment& p);

#endif // SEGMENT_H
