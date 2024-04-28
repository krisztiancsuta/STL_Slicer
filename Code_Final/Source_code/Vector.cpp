#include "Vector.h"
#include <cmath>
#include <iostream>
const double epsilon = 1e-10;

double Vector::getLength() const { return std::sqrt(XYZ[0] * XYZ[0] + XYZ[1] * XYZ[1] + XYZ[2] * XYZ[2]); }

double Vector::dot(const Vector& v1, const Vector& v2) {
    return v1.XYZ[0] * v2.XYZ[0] + v1.XYZ[1] * v2.XYZ[1] + v1.XYZ[2] * v2.XYZ[2];
}

Vector Vector::cross(const Vector& n1, const Vector& n2) {
    return Vector(n1.XYZ[1] * n2.XYZ[2] - n1.XYZ[2] * n2.XYZ[1],
        n1.XYZ[2] * n2.XYZ[0] - n1.XYZ[0] * n2.XYZ[2],
        n1.XYZ[0] * n2.XYZ[1] - n1.XYZ[1] * n2.XYZ[0]);

}

void Vector::print(std::ostream& os) const {
    if (&os != &std::cout)// ha fileba akarunk irni mas a formatum
    {
        os << " X" << XYZ[0] << " Y" << XYZ[1] << " Z" << XYZ[2];
    }
    else
        os << "Vector(" << XYZ[0] << "," << XYZ[1] << "," << XYZ[2] << ")";
}
void Vector::read(std::istream& is) {
    is >> XYZ[0] >> XYZ[1] >> XYZ[2];
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    v.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Vector& v) {

    v.read(is); // beolvassa a pontba az ertekeket
    return is;
}

Vector Vector::operator-(const Vector& B) const {

    return Vector(XYZ[0] - B.XYZ[0], XYZ[1] - B.XYZ[1], XYZ[2] - B.XYZ[2]);
}
Vector Vector::operator+(const Vector& B) const {
    return Vector(XYZ[0] + B.XYZ[0], XYZ[1] + B.XYZ[1], XYZ[2] + B.XYZ[2]);
}
bool Vector::operator<(double& n) const {
    return XYZ[2] < n;
}
bool Vector::operator>(double& n) const {
    return XYZ[2] > n;
}
void operator>>(double& n, Vector const& v) {
    n = v.XYZ[2];
}

Vector& Vector::operator*(double t) {
    XYZ[0] *= t;
    XYZ[1] *= t;
    XYZ[2] *= t;
    return *this;
}

bool Vector::operator==(const Vector& v) const {
    return (std::abs(v.XYZ[0] - XYZ[0]) < epsilon && std::abs(v.XYZ[1] - XYZ[1]) < epsilon && std::abs(v.XYZ[2] - XYZ[2]) < epsilon);
}
