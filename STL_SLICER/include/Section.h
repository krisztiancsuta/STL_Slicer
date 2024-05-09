#pragma once
#include "Vector.h"
#include "Plane.h"
#include <iostream>

/**
 * @brief Represents a section defined by two vectors.
 */
class Section {
    Vector section[2]; // v1 = section[0], v2 = section[1]
public:

    /**
     * @brief Default constructor for Section.
     * @param v1 The first vector of the section.
     * @param v2 The second vector of the section.
     */
    Section(Vector v1 = Vector(), Vector v2 = Vector());

    /**
     * @brief Calculates the intersection point between the section and a plane.
     * @param plane The plane to intersect with.
     * @param success Indicates if the intersection was successful.
     * @return The intersection point as a Vector.
     */
    Vector PlaneInterSection(const Plane& plane, bool& isValidPoint) const;

    /**
     * @brief Prints the section to the specified output stream.
     * @param os The output stream to print to.
     */
    void print(std::ostream& os = std::cout) const;

    /**
     * @brief Checks if two sections are equal.
     * @param other The other section to compare with.
     * @return True if the sections are equal, false otherwise.
     */
    bool operator==(const Section& other) const;

    /**
     * @brief Checks if the two vectors connect and have the same direction
     * @param other The other section to compare with.
     * @return True if the endpoint of the first vector is equal to the starting point of the second vector.
     */
    bool operator<<=(Section& other) const;
};

/**
 * @brief Overloads the << operator to print the section to the specified output stream.
 * @param os The output stream to print to.
 * @param section The section to print.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream& os, const Section& section);