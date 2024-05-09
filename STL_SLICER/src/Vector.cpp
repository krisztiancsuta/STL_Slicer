#include "Vector.h"
#include <cmath>
#include <iostream>

const double epsilon = 1e-10;

/**
 * @brief Calculate the length of the vector.
 * @return The length of the vector.
 */
double Vector::getLength() const {
    return std::sqrt(XYZ[0] * XYZ[0] + XYZ[1] * XYZ[1] + XYZ[2] * XYZ[2]);
}

/**
 * @brief Calculate the dot product of two vectors.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The dot product of the two vectors.
 */
double Vector::dot(const Vector& v1, const Vector& v2) {
    return v1.XYZ[0] * v2.XYZ[0] + v1.XYZ[1] * v2.XYZ[1] + v1.XYZ[2] * v2.XYZ[2];
}

/**
 * @brief Calculate the cross product of two vectors.
 * @param n1 The first vector.
 * @param n2 The second vector.
 * @return The cross product of the two vectors.
 */
Vector Vector::cross(const Vector& n1, const Vector& n2) {
    return Vector(n1.XYZ[1] * n2.XYZ[2] - n1.XYZ[2] * n2.XYZ[1],
        n1.XYZ[2] * n2.XYZ[0] - n1.XYZ[0] * n2.XYZ[2],
        n1.XYZ[0] * n2.XYZ[1] - n1.XYZ[1] * n2.XYZ[0]);
}

/**
 * @brief Print the vector to the output stream.
 * @param os The output stream.
 */
void Vector::print(std::ostream& os) const {
    if (&os != &std::cout) {
        // If the output stream is not cout, we use a different format.
        os << " X" << XYZ[0] << " Y" << XYZ[1] << " Z" << XYZ[2];
    }
    else {
        os << "Vector(" << XYZ[0] << "," << XYZ[1] << "," << XYZ[2] << ")";
    }
}

/**
 * @brief Read the vector from the input stream.
 * @param is The input stream.
 */
void Vector::read(std::istream& is) {
    is >> XYZ[0] >> XYZ[1] >> XYZ[2];
}

/**
 * @brief Overload the << operator to print the vector.
 * @param os The output stream.
 * @param v The vector to be printed.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    v.print(os);
    return os;
}

/**
 * @brief Overload the >> operator to read the vector.
 * @param is The input stream.
 * @param v The vector to be read.
 * @return The input stream.
 */
std::istream& operator>>(std::istream& is, Vector& v) {
    v.read(is);
    return is;
}

/**
 * @brief Overload the - operator to subtract two vectors.
 * @param B The vector to be subtracted.
 * @return The resulting vector.
 */
Vector Vector::operator-(const Vector& B) const {
    return Vector(XYZ[0] - B.XYZ[0], XYZ[1] - B.XYZ[1], XYZ[2] - B.XYZ[2]);
}

/**
 * @brief Overload the + operator to add two vectors.
 * @param B The vector to be added.
 * @return The resulting vector.
 */
Vector Vector::operator+(const Vector& B) const {
    return Vector(XYZ[0] + B.XYZ[0], XYZ[1] + B.XYZ[1], XYZ[2] + B.XYZ[2]);
}

/**
 * @brief Overload the < operator to compare the Z component of the vector with a double.
 * @param n The double value to be compared with.
 * @return True if the Z component is less than n, false otherwise.
 */
bool Vector::operator<(double& n) const {
    return XYZ[2] < n;
}

/**
 * @brief Overload the > operator to compare the Z component of the vector with a double.
 * @param n The double value to be compared with.
 * @return True if the Z component is greater than n, false otherwise.
 */
bool Vector::operator>(double& n) const {
    return XYZ[2] > n;
}

/**
 * @brief Overload the >> operator to assign the Z component of the vector to a double.
 * @param n The double variable to be assigned.
 * @param v The vector.
 */
void operator>>(double& n, Vector const& v) {
    n = v.XYZ[2];
}

/**
 * @brief Multiply the vector by a scalar value.
 * @param t The scalar value.
 * @return The resulting vector.
 */
Vector& Vector::operator*(double t) {
    XYZ[0] *= t;
    XYZ[1] *= t;
    XYZ[2] *= t;
    return *this;
}

/**
 * @brief Check if two vectors are equal within a small epsilon value.
 * @param v The vector to be compared with.
 * @return True if the vectors are equal, false otherwise.
 */
bool Vector::operator==(const Vector& v) const {
    return (std::abs(v.XYZ[0] - XYZ[0]) < epsilon && std::abs(v.XYZ[1] - XYZ[1]) < epsilon && std::abs(v.XYZ[2] - XYZ[2]) < epsilon);
}

/**
 * @brief Convert a float array to a Vector.
 * @param arr The float array.
 */
void Vector::convert(const float* arr) {
    XYZ[0] = static_cast<double>(arr[0]);
    XYZ[1] = static_cast<double>(arr[1]);
    XYZ[2] = static_cast<double>(arr[2]);
}
