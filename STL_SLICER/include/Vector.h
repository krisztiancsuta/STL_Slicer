#pragma once
#include <iostream>

/**
 * @brief The Vector class represents a 3D vector.
 */
class Vector
{
private:
    double XYZ[3];
    friend void operator>>(double&, Vector const&);

public:
    /**
     * @brief Constructor for the Vector class.
     * @param x The x-coordinate of the vector.
     * @param y The y-coordinate of the vector.
     * @param z The z-coordinate of the vector.
     */
    Vector(double x = 999, double y = 999, double z = 999)
    {
        XYZ[0] = x;
        XYZ[1] = y;
        XYZ[2] = z;
    };

    /**
     * @brief Returns the length of the Vector.
     * @return The length of the Vector.
     */
    double getLength() const;

    /**
     * @brief Calculates the dot product of two Vectors.
     * @param v1 The first Vector.
     * @param v2 The second Vector.
     * @return The dot product of the two Vectors.
     */
    static double dot(const Vector& v1, const Vector& v2);

    /**
     * @brief Calculates the cross product of two Vectors.
     * @param v1 The first Vector.
     * @param v2 The second Vector.
     * @return The cross product of the two Vectors.
     */
    static Vector cross(const Vector& v1, const Vector& v2);

    /**
     * @brief Prints out a Vector to the output stream.
     * @param os The output stream.
     */
    void print(std::ostream& os = std::cout) const;

    /**
     * @brief Reads a Vector from input stream.
     * @param is The input stream.
     */
    void read(std::istream& is = std::cin);

    /**
     * @brief Subtracts two Vectors: v1 - v2.
     * @param v The Vector to subtract.
     * @return The resulting Vector.
     */
    Vector operator-(const Vector& v) const;

    /**
     * @brief Adds two Vectors together: v1 + v2.
     * @param v The Vector to add.
     * @return The resulting Vector.
     */
    Vector operator+(const Vector& v) const;

    /**
     * @brief Compares the z coordinate with a double.
     * @param d The double to compare with.
     * @return True if the z coordinate is less than the double, false otherwise.
     */
    bool operator<(double& d) const;

    /**
     * @brief Compares the z coordinate with a double.
     * @param d The double to compare with.
     * @return True if the z coordinate is greater than the double, false otherwise.
     */
    bool operator>(double& d) const;

    /**
     * @brief Multiply all the coordinates with a scalar value.
     * @param scalar The scalar value to multiply with.
     * @return The resulting Vector.
     */
    Vector& operator*(double scalar);

    /**
     * @brief Compares two Vectors.
     * @param v The Vector to compare with.
     * @return True if the two Vectors are equal, false otherwise.
     */
    bool operator==(const Vector& v) const;

    /**
     * @brief Converts the coordinates from float array to double.
     * @param arr The float array containing the coordinates.
     */
    void convert(const float* arr);
};

/**
 * @brief Prints out a Vector to the output stream.
 * @param os The output stream.
 * @param v The Vector to print.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, Vector const& v);

/**
 * @brief Reads a Vector from input stream.
 * @param is The input stream.
 * @param v The Vector to read into.
 * @return The input stream.
 */
std::istream& operator>>(std::istream& is, Vector& v);

/**
 * @brief Streams the Z coordinate into the double.
 * @param d The double to store the Z coordinate.
 * @param v The Vector to extract the Z coordinate from.
 */
void operator>>(double& d, Vector const& v);