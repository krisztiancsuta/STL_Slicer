#include "Vector.h"
#include <cmath>


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
    os << *this;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "Vector(" << v.XYZ[0] << "," << v.XYZ[1] << "," << v.XYZ[2] << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Vector& v) {

    is >> v.XYZ[0] >> v.XYZ[1] >> v.XYZ[2]; // beolvassa a pontba az ertekeket
    return is;
}

Vector Vector::operator-(const Vector& B) const {

    return Vector(XYZ[0] - B.XYZ[0], XYZ[1] - B.XYZ[1], XYZ[2] - B.XYZ[2]);
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