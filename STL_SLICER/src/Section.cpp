#include "Section.h"
#include "Plane.h"
#include "Vector.h"
#include <iostream>


Vector Section::PlaneInterSection(const Plane& plane, bool& isValidPoint) const {
    // Calculate the intersection point between the section and a plane
    // using the formula: t = dot(ref_point - v1, normal) / dot(v2 - v1, normal)
    double t = Vector::dot(plane.getRef() - section[0], plane.getNormal()) /
        Vector::dot((section[1] - section[0]), plane.getNormal());

    if (t <= 0 || t >= 1) {
        isValidPoint = false;
    }

    // Calculate the intersection point
    Vector result = section[0] + Vector((section[1] - section[0]) * t);
    return result;
}

Section::Section(Vector v1, Vector v2) {
    // Initialize the section with two vectors
    section[0] = v1;
    section[1] = v2;
}


void Section::print(std::ostream& os) const {
    if (&os != &std::cout) {
        // If writing to a file, only output the second vector of the section
        os << section[1];
    }
    else {
        // If writing to std::cout, output both vectors of the section
        os << "Section v1:" << section[0] << " ,v2:" << section[1];
    }
}


std::ostream& operator<<(std::ostream& os, const Section& s) {
    // Overloaded << operator to print the section
    s.print(os);
    return os;
}


bool Section::operator==(const Section& other) const {
    // Check if two sections are equal by comparing their vectors
    return section[0] == other.section[0] && section[1] == other.section[1];
}



bool Section::operator<<=(Section& rs) const {
    if (section[1] == rs.section[1]) {
        // If the sections are facing each other, swap the coordinates of rs
        Vector tmp = rs.section[0];
        rs.section[0] = rs.section[1];
        rs.section[1] = tmp;
    }
    return section[1] == rs.section[0]; // Return true if v2 = rs.v1
}