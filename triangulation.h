#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>

#include "point.h"
#include "segment.h"
#include "triangle.h"

class Data;

class Triangulation
{
public:
    Triangulation();
    Triangulation(Data* d);
    int getOrdre() const;
    std::vector<Point*> getPoints() const;
    Point* getPoint(int index) const;
    void addPoint(Point* p);
    void addPoints(Point** p, int size);
    std::vector<Segment*> getSegments() const;
    Segment* getSegment(int index) const;
    Segment* getSegment(Point *p, Point *q) const;
    void addSegment(Segment* s);
    void addSegments(Segment** s, int size);
    void addTriangle(Triangle *t);
    std::vector<Triangle*> getTriangles() const;
    void print() const;
    void scanTriangles();
    void calculMilieux(std::vector<Point*> points);
    void mileuxSegmentsTriangles(std::vector<Triangle*> triangles, int nbSegments);

    friend std::ostream& operator<<(std::ostream&, const Triangulation&);
    friend std::istream& operator>>(std::istream&, Triangulation&);

private:
    std::vector<Point*> m_points;
    std::vector<Segment*> m_segments;
    std::vector<Triangle*> m_triangles;
    int m_ordre;
};

std::ostream& operator<<(std::ostream& out, const Triangulation& t);
std::istream& operator>>(std::istream& in, Triangulation& t);

#endif // TRIANGULATION_H
