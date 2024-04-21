
#pragma once
#include"Vector.h"
#include"Plane.h"


class Section {
    Vector section[2];
public:
    Vector PlaneInterSection(const Plane&) const; //Vector itt most egy pontot jelol
};