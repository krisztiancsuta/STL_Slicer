#include "Section.h"
#include "Plane.h"
#include "Vector.h"
#include <iostream>
Vector Section::PlaneInterSection(const Plane& plane, bool& isValidPoint) const {
    // t = dot(ref_point - v1),normal) / (dot(v2 - v1),normal));
    double t = Vector::dot(plane.getRef() - section[0], plane.getNormal()) /
        (Vector::dot((section[1] - section[0]), plane.getNormal()));

    if (t <= 0 || t >= 1) {
        isValidPoint = false;
    }

    Vector result = section[0] + Vector((section[1] - section[0]) * t); // megkapjuk a pontot
    return result;
}

Section::Section(Vector v1, Vector v2) {
    section[0] = v1;
    section[1] = v2;
}


void Section::print(std::ostream& os)const {
    if (&os != &std::cout)// ha fileba akarunk irni mas a formatum
    {
        os << section[1]; // mindig csak a v2 irjuk ki 
    }
    else
        os << "Section v1:" << section[0] << " ,v2:" << section[1];

}
std::ostream& operator<<(std::ostream& os, const Section& s) {
    s.print(os);
    return os;
}

bool Section::operator==(const Section& other)const {
    return  section[0] == other.section[0] && section[1] == other.section[1];
}

bool Section::operator<<= (Section& rs)const {
    if (section[1] == rs.section[1]) {
        //ha egymassal szembe neznek a szakaszok akkor rs koordinatait megcserelem
        Vector tmp = rs.section[0];
        rs.section[0] = rs.section[1];    //swap v1 = v2
        rs.section[1] = tmp;    //v2 = v1
    }
    return section[1] == rs.section[0];//return 1 if v2 = rs.v1
}