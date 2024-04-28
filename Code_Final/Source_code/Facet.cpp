#include "Facet.h"
#include "Section.h"
#include <iostream>
#include "Vector.h"

std::ostream& operator<<(std::ostream& os, const Facet& f) {
    f.print(os);
    return os;
}

Section Facet::PlaneIntersection(const Plane& plane, bool& isValidSection) {
    //visszaad egy szakaszt
    Section Sections[3] = { Section(verteces[0], verteces[1]),
                            Section(verteces[0], verteces[2]),
                            Section(verteces[1], verteces[2]) };
    Vector section_points[2];
    unsigned j = 0;//metszespontokat szamolja
    for (unsigned i = 0; i < 3; i++)
    {
        bool isValidPoint = true;
        Vector tmp = Sections[i].PlaneInterSection(plane, isValidPoint);
        if (isValidPoint)
        {
            if (j == 0) {
                section_points[j++] = tmp;
            }
            else {// van e mar ugyanolyan pont a szakaszban
                bool isSimilar = false;
                for (int k = 0; k < j; k++) {
                    if (tmp == section_points[k]) {
                        isSimilar = true;
                        break;
                    }
                }
                if (!isSimilar) {
                    section_points[j++] = tmp;
                }
            }
        }
    }
    if (j != 2) {//mindig pontosan 2 metszespontom lesz ha van megoldas
        isValidSection = false;
    }
    return Section(section_points[0], section_points[1]);
} // kiszamolja egy facet és sík metszésszakaszát

void Facet::print(std::ostream& os)const {
    os << "Facet A:" << verteces[0] << " ,B:" << verteces[1] << " ,C:" << verteces[2];
}