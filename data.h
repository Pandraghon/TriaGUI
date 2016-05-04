#ifndef DATA_H
#define DATA_H

#include <vector>

#include "triangulation.h"
#include "point.h"

class Data
{
public:
    Data();
    ~Data();

    std::vector<Triangulation*> getTriangulations() const;
    Triangulation* getTriangulation(int index) const;

private:
    std::vector<Triangulation*> m_triangs;
    std::vector<Point*> m_points;

};

#endif // DATA_H
