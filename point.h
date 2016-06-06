#ifndef POINT_H
#define POINT_H

#include <algorithm>
#include <vector>
#include <set>

class Segment;

class Point
{
public:
    Point();
    Point(float x, float y);
    Point(Point *p1, Point *p2);
    //void addNeighbor(Point* p);
    void addSegment(Segment* s);
    void setX(float x);
    void setY(float y);
    float getX() const;
    float getY() const;
    std::string getNom() const;
    std::string getCoord() const;
    Segment* getSegment(int i) const;
    int nbSegments() const;
    bool isBefore(Point* p) const;
    bool isSegment(Point* p);
    bool isLeft(Point* p, Point* q) const;
    bool isLeft(const Segment* pq) const;
    void print() const;
    int getIndex() const;
    bool isSite() const;
    int nbGenerateurs() const;
    static void initIndex();

    friend std::ostream& operator<<(std::ostream&, const Point&);
    friend std::istream& operator>>(std::istream&, Point*);

    int getOrder() const;
    void setOrder(int order);

private:
    float m_x, m_y;
    //std::vector<Point*> m_neighbors;
    std::vector<Segment*> m_segments;
    std::set<Point*> m_generateurs;
    std::string m_nom;
    int m_order;
    static int nb;
    int m_index;
};

std::ostream& operator<<(std::ostream& out, const Point& p);
std::istream& operator>>(std::istream& in, Point* p);

#endif // POINT_H
