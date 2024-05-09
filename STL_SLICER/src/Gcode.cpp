#include "Gcode.h"
#include <iostream>
#include <fstream> 
#include "Section.h"
#include <sstream>

// Function to sort the sections
void Gcode::SortSections(std::vector<Section>& sections) {
    // Select the first section
    for (unsigned i = 0; i < sections.size(); i++) {
        for (unsigned j = i + 1; j < sections.size(); j++) {
            if (sections[i] <<= sections[j]) { // If the two sections can be concatenated
                // Swap sections[j] with sections[i+1]
                std::swap(sections[i + 1], sections[j]);
            }
        }
    }
}

// Function to write the Gcode
void Gcode::WriteGcode(std::ofstream& gcode, std::vector<Section>const& sections) {
    unsigned i;
    for (i = 0; i < sections.size(); i++) {
        gcode << "G1 F1500" << sections[i] << " E" << (i + 1) << std::endl;
    }

}
