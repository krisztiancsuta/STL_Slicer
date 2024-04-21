#pragma once

#include "Vector.h"


class Plane {
    Vector ref_point;
    Vector normal;
public:
    Plane(Vector ref_point, Vector normal) :ref_point(ref_point), normal(normal) {};
};