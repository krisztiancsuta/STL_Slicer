#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Facet.h"

/**
 * @brief The STLFile class represents an STL file.
 */
class STLFile
{
public:
    static double minZ; /**< The minimum Z coordinate value in the STL file. */
    static double maxZ; /**< The maximum Z coordinate value in the STL file. */

    /**
     * @brief Reads the STL file in binary or text format.
     * @param filename The path to the STL file.
     * @return A vector of Facet objects representing the facets in the STL file.
     */
    static std::vector<Facet> readSTLFile(const std::string& filename);

    /**
     * @brief Checks if the file is in binary STL format.
     * @param filename The path to the STL file.
     * @return True if the file is in binary format, false otherwise.
     */
    static bool isBinarySTL(const std::string& filename);
};