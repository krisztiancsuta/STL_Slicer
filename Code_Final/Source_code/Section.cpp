#include "Section.h"
#include "Plane.h"
#include "Vector.h"
#include <iostream>
Vector Section::PlaneInterSection(const Plane& plane) const {
    // t = dot(ref_point - v1),normal) / (dot(v2 - v1),normal));
    double t = Vector::dot(plane.getRef() - section[0], plane.getNormal()) /
        (Vector::dot((section[1] - section[0]), plane.getNormal()));

    if (std::isnan(t) || std::isinf(t) || t < 0) {
        return(Vector()); // ha nincs metszespont
    }

    Vector result = section[0] + Vector((section[1] - section[0]) * t); // megkapjuk a pontot
    return result;

}

Section::Section(Vector v1, Vector v2) {
    section[0] = v1;
    section[1] = v2;
}


void Section::print(std::ostream&)const {
    std::cout << "Section v1:" << section[0] << " ,v2:" << section[1] << std::flush;

}

bool Section::operator==(const Section& other)const {
    return  section[0] == other.section[0] && section[1] == other.section[1];
}
