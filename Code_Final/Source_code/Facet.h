#pragma once 
#include "Vector.h"
#include "Plane.h"
#include "Section.h"
class Facet
{
private:
     Vector Sections[3];
public:
    Section PlaneIntersection(const Plane&); // kiszamolja egy facet és sík metszésszakaszát
};
