#pragma once 

#include "Vector.h"
#include "Plane.h"
#include "Section.h"

/**
 * @class Facet
 * @brief Represents a facet in a 3D model.
 *
 * The Facet class stores the vertices of a facet and provides methods for calculating
 * the intersection of the facet with a plane and printing the facet.
 */
class Facet
{
private:
    Vector verteces[3]; // Array to store the vertices of the facet (v1, v2, v3 in right hand rule order).
    friend std::ostream& operator<<(std::ostream&, const Facet&);

public:
    /**
     * @brief Constructs a Facet object with three vertices.
     * @param a The first vertex of the facet.
     * @param b The second vertex of the facet.
     * @param c The third vertex of the facet.
     */
    Facet(Vector a, Vector b, Vector c) { verteces[0] = a; verteces[1] = b; verteces[2] = c; };

    /**
     * @brief Calculates the intersection of the facet and a plane.
     * @param plane The plane to intersect with.
     * @param intersectionExists Set to true if an intersection exists, false otherwise.
     * @return The intersection section of the facet and the plane.
     */
    Section PlaneIntersection(const Plane& plane, bool& intersectionExists);

    /**
     * @brief Prints the facet to the specified output stream.
     * @param os The output stream to print the facet to.
     */
    void print(std::ostream& os = std::cout) const;
};
