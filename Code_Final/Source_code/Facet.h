#pragma once 
#include "Vector.h"
#include "Plane.h"
#include "Section.h"

class Facet
{
private:
    Vector Sections[3];
    friend std::ostream& operator<<(std::ostream&, const Facet&);
public:
    Facet(Vector a, Vector b, Vector c) { Sections[0] = a;Sections[1] = b;Sections[2] = c; };
    Section PlaneIntersection(const Plane&); // kiszamolja egy facet és sík metszésszakaszát

};

std::ostream& operator<<(std::ostream&, const Facet&);