#pragma once
#include <iostream>
class Vector
{
private:
    double XYZ[3];
    friend std::ostream& operator<<(std::ostream&, Vector const&);
    friend std::istream& operator>>(std::istream&, Vector&);
    friend void operator>>(double&, Vector const&);
public:
    Vector(double x = 0, double y = 0, double z = 0) {
        XYZ[0] = x;
        XYZ[1] = y;
        XYZ[2] = z;
    };
    double getLength() const;
    static double dot(const Vector&, const Vector&);
    static Vector cross(const Vector&, const Vector&);

    void print(std::ostream & = std::cout) const;

    Vector operator-(const Vector&) const;//kérdés hogy referenciát vagy értéket adjak vissza
    bool operator<(double&)const; // egy vektor z koordinatajat osszehasonlitom egy doublelal -> STLFIle.h
    bool operator>(double&)const;



};
std::ostream& operator<<(std::ostream&, Vector const&);
std::istream& operator>>(std::istream&, Vector&);
void  operator>>(double&, Vector const&);
