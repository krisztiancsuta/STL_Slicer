#include "Facet.h"
#include "Section.h"
#include <iostream>
#include "Vector.h"

std::ostream& operator<<(std::ostream& os, const Facet& f) {
    os << "Facet A:" << f.verteces[0] << " ,B:" << f.verteces[1] << " ,C:" << f.verteces[2];
    return os;
}

Section Facet::PlaneIntersection(const Plane& plane) {
    //visszaad egy szakaszt
    Section Sections[3] = { Section(verteces[0], verteces[1]),
                            Section(verteces[0], verteces[2]),
                            Section(verteces[1], verteces[2]) };
    Vector section_points[2];
    for (unsigned i = 0, j = 0; i < 3; i++)
    {
        Vector tmp = Sections[i].PlaneInterSection(plane);
        if (!(tmp == Vector()))
        {
            if (j == 0) {
                section_points[j++] = tmp;
            }
            else {
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
        if (j == 2) {//mindig pontosan 2 metszespontom lesz ha van megoldas
            return Section(section_points[0], section_points[1]); // visszaterek a szakasszal
        }
    }
    return Section();
} // kiszamolja egy facet és sík metszésszakaszát

void Facet::print(std::ostream& os)const {
    os << *this << std::flush;
}