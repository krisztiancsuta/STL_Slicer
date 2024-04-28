#pragma once

#include<iostream>
#include <vector>
#include "Section.h"
#include "Vector.h"
#include "Facet.h"

class Gcode {

public:

    static void WriteGcode(std::ofstream&, std::vector<Section>const&);
    static  void SortSections(std::vector<Section>&);

};