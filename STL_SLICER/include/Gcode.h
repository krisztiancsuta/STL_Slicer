#pragma once

#include<iostream>
#include <vector>
#include "Section.h"
#include "Vector.h"
#include "Facet.h"

/**
 * @brief The Gcode class provides functions for generating G-code instructions.
 */
class Gcode {

public:

    /**
     * @brief Writes one layer of the sliced 3D model into gcode.
     * @param ofs The output stream to write the G-code to.
     * @param sections The vector of sections to generate G-code from.
     */
    static void WriteGcode(std::ofstream& ofs, std::vector<Section> const& sections);

    /**
     * @brief Sorts the sections in order to create a continuous path for the printer.
     * @param sections The vector of sections to be sorted.
     */
    static void SortSections(std::vector<Section>& sections);

};
