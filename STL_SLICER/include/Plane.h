#pragma once

#include "Vector.h"

/**
 * @class Plane
 * @brief Represents a plane in three-dimensional space.
 */
class Plane {
    Vector ref_point; /**< The reference point on the plane. */
    Vector normal; /**< The normal vector of the plane. */

public:
    /**
     * @brief Constructs a Plane object with the given reference point and normal vector.
     * @param ref_point The reference point on the plane.
     * @param normal The normal vector of the plane.
     */
    Plane(const Vector& ref_point, const Vector& normal) : ref_point(ref_point), normal(normal) {};

    /**
     * @brief Gets the reference point of the plane.
     * @return The reference point of the plane.
     */
    const Vector& getRef() const { return ref_point; };

    /**
     * @brief Gets the normal vector of the plane.
     * @return The normal vector of the plane.
     */
    const Vector& getNormal() const { return normal; };
};
