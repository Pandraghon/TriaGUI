#ifndef POINT_H
#define POINT_H

#include <algorithm>
#include <vector>

class Segment;

class Point
{
public:
    Point();
    Point(float x, float y);
    //void addNeighbor(Point* p);
    void addSegment(Segment* s);
    void setX(float x);
    void setY(float y);
    float getX() const;
    float getY() const;
    std::string getNom() const;
    bool isBefore(Point* p) const;
    bool isSegment(Point* p);
    bool isLeft(Point* p, Point* q) const;
    bool isLeft(const Segment* pq) const;
    void print() const;

    friend std::ostream& operator<<(std::ostream&, const Point&);
    friend std::istream& operator>>(std::istream&, Point&);

private:
    float m_x, m_y;
    //std::vector<Point*> m_neighbors;
    std::vector<Segment*> m_segments;
    std::string m_nom;
    static int nb;
};

std::ostream& operator<<(std::ostream& out, const Point& p);
std::istream& operator>>(std::istream& in, Point& p);

#endif // POINT_H
