
#pragma once
#include"Vector.h"
#include"Plane.h"
#include <iostream>

class Section {
    Vector section[2]; // v1 = section[0] , v2 = section[1]
public:

    Section(Vector = Vector(), Vector = Vector());
    Vector PlaneInterSection(const Plane&) const; //Vector itt most egy pontot jelol
    void print(std::ostream & = std::cout)const;
    bool operator==(const Section&)const;

};
