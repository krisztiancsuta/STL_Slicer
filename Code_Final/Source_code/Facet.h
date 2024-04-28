#pragma once 
#include "Vector.h"
#include "Plane.h"
#include "Section.h"

class Facet
{
private:
    Vector verteces[3]; // v1, v2, v3 in right hand rule order
    friend std::ostream& operator<<(std::ostream&, const Facet&);
public:
    Facet(Vector a, Vector b, Vector c) { verteces[0] = a;verteces[1] = b;verteces[2] = c; };
    Section PlaneIntersection(const Plane&, bool&); // kiszamolja egy facet és sík metszésszakaszát
    void print(std::ostream & = std::cout)const;
};

std::ostream& operator<<(std::ostream&, const Facet&);