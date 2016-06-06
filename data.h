#ifndef DATA_H
#define DATA_H

#include <QVariant> // serialization

#include <vector>

#include "triangulation.h"
#include "point.h"

class Triangulation;

class Data
{
public:
    Data();
    ~Data();

    std::vector<Triangulation*> getTriangulations() const;
    Triangulation* getTriangulation(int index) const;
    unsigned int nbTriangulation() const;
    void addTriangulation(Triangulation *t);
    void nextOrder();

    void exportToEPS(const std::string& filename);
    void clear();

    friend std::ostream& operator<<(std::ostream&, const Data&);
    friend std::istream& operator>>(std::istream&, Data&);

private:
    std::vector<Triangulation*> m_triangs;

};

std::ostream& operator<<(std::ostream& out, const Data& v);
std::istream& operator>>(std::istream& in, Data& v);

#endif // DATA_H
