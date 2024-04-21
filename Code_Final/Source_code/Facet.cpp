#include "Facet.h"

#include<iostream>
#include "Vector.h"

std::ostream& operator<<(std::ostream& os, const Facet& f) {
    os << "Facet\nA:" << f.Sections[0] << " ,B:" << f.Sections[1] << " ,C:" << f.Sections[2];
    return os;
}

Section PlaneIntersection(const Plane& plane) {

} // kiszamolja egy facet és sík metszésszakaszát
