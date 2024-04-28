
#pragma once
#include"Vector.h"
#include"Plane.h"
#include <iostream>

class Section {
    Vector section[2]; // v1 = section[0] , v2 = section[1]
public:

    Section(Vector = Vector(), Vector = Vector());
    Vector PlaneInterSection(const Plane&, bool&) const; //Vector itt most egy pontot 

    void print(std::ostream & = std::cout)const;
    bool operator==(const Section&)const;
    bool operator<<= (Section&)const;//megnezi hogy v2 koordinata megegyezik e rs.v1 el, ha nem akkor felcsereli a szakasz iranyat
};

std::ostream& operator<<(std::ostream&, const Section&);