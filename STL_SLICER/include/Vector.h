#pragma once
#include <iostream>
class Vector
{
private:
    double XYZ[3];


    friend void operator>>(double&, Vector const&);
public:
    Vector(double x = 999, double y = 999, double z = 999) {
        XYZ[0] = x;
        XYZ[1] = y;
        XYZ[2] = z;
    };
    double getLength() const;
    static double dot(const Vector&, const Vector&);
    static Vector cross(const Vector&, const Vector&);

    void print(std::ostream & = std::cout) const;
    void read(std::istream & = std::cin);

    Vector operator-(const Vector&) const;//kérdés hogy referenciát vagy értéket adjak vissza
    Vector operator+(const Vector&) const;
    bool operator<(double&)const; // egy vektor z koordinatajat osszehasonlitom egy doublelal -> STLFIle.h
    bool operator>(double&)const;
    Vector& operator*(double);
    bool operator==(const Vector&)const;
    void convert(const float* arr);



};
std::ostream& operator<<(std::ostream&, Vector const&);
std::istream& operator>>(std::istream&, Vector&);
void  operator>>(double&, Vector const&);
