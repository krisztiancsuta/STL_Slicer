#pragma once
#include <iostream>
class Vector
{
private:
    double XYZ[3];
public:
    double getLength() const;
    static double dot(const Vector&, const Vector&);
    static Vector cross(const Vector&, const Vector&);

    void print() const;

    Vector operator-(const Vector&) const;//kérdés hogy referenciát vagy értéket adjak vissza
    std::istream& operator>>(std::istream&, Vector&);
};
