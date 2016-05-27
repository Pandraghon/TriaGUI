#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>

#include "point.h"
#include "segment.h"
#include "triangle.h"

class Triangulation
{
public:
    Triangulation();
    std::vector<Point*> getPoints() const;
    Point* getPoint(int index) const;
    void addPoint(Point* p);
    void addPoints(Point** p, int size);
    std::vector<Segment*> getSegments() const;
    Segment* getSegment(int index) const;
    void addSegment(Segment* s);
    void addSegments(Segment** s, int size);
    void addTriangle(Triangle *t);
    void print() const;
    void scanTriangles();

    friend std::ostream& operator<<(std::ostream&, const Triangulation&);
    friend std::istream& operator>>(std::istream&, Triangulation&);

private:
    std::vector<Point*> m_points;
    std::vector<Segment*> m_segments;
    std::vector<Triangle*> m_triangles;
};

std::ostream& operator<<(std::ostream& out, const Triangulation& t);
std::istream& operator>>(std::istream& in, Triangulation& t);

#endif // TRIANGULATION_H
