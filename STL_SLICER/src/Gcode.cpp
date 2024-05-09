


#include "Gcode.h"
#include <iostream>
#include <fstream> 
#include "Section.h"

void Gcode::SortSections(std::vector<Section>& sections) {
    //kivalasztjuk az elso szakaszt 
    for (unsigned i = 0;i < sections.size(); i++)
    {
        for (unsigned j = i + 1; j < sections.size(); j++)
        {
            if (sections[i] <<= sections[j]) {// ha a ket szakasz összefűzhető
                //swap sections[j], sections[i+1]
                std::swap(sections[i + 1], sections[j]);
            }
        }
    }
}


void Gcode::WriteGcode(std::ofstream& gcode, std::vector<Section>const& sections) {

    for (unsigned i = 0; i < sections.size(); i++)
    {
        gcode << "G1 F1500" << sections[i] << " E" << (i + 1) << std::endl;

    }
}

