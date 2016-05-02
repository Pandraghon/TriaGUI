#ifndef POINT_H
#define POINT_H

#include <algorithm>
#include <vector>

class Point
{
public:
    Point();
    Point(float x, float y);
    void addNeighbor(Point* p);
    void setX(float x);
    void setY(float y);
    float getX() const;
    float getY() const;

private:
    float m_x, m_y;
    std::vector<Point*> m_neighbors;
};

#endif // POINT_H
