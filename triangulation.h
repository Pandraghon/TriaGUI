#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>

#include "point.h"
#include "segment.h"
#include "triangle.h"

class Data;
class Triangle;

class Triangulation
{
public:
    Triangulation();
    Triangulation(Data* d);
    void initVoisins(int nbPoints);
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
    Triangle* getTriangle(int i) const;
    std::vector<Triangle*> getTriangles() const;
    void print() const;
    void scanTriangles();
    void calculNextOrdrePoints(std::vector<Triangle*> triangles, int nbSegments);
    void generateNextOrdre();
    //void calculMilieux(std::vector<Point*> points);
    //void mileuxSegmentsTriangles(std::vector<Triangle*> triangles, int nbSegments);

    void clear();

    friend std::ostream& operator<<(std::ostream&, const Triangulation&);
    friend std::istream& operator>>(std::istream&, Triangulation*);
    Triangle ***voisins;

private:
    std::vector<Point*> m_points;
    std::vector<Segment*> m_segments;
    std::vector<Triangle*> m_triangles;
    int m_ordre;
};

std::ostream& operator<<(std::ostream& out, const Triangulation& t);
std::istream& operator>>(std::istream& in, Triangulation* t);

#endif // TRIANGULATION_H
