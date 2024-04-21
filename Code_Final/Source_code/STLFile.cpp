#include "STLFile.h"
#include "Facet.h"
#include <fstream>
#include <sstream>
#include <iostream>
std::vector<Facet> read_STL(const std::string& filename, const std::string& mode) {

    std::vector<Facet> facets; //letrehozok egy vektort amibe a facet-ek lesznek ez fog dinimaikusan novekedni

    if (mode == "binary")
    {

    }
    else//Read file in text format
    {
        std::ifstream stl_file(filename);
        if (!stl_file.is_open()) {
            std::cerr << "Could not open file " << filename << std::endl;
            return facets;
        }

        std::string line;
        while (std::getline(stl_file, line)) { // beolvassa az elso sort
            Vector n;
            Point verteces[3];

            if (line.find("facet normal") != std::string::npos) {
                //
                //std::istringstream sin(line.substr(line.find("facet normal") + 12)); // Initialize with the part after "facet normal"
                //sin >> n; // overloaded >> operator
                std::getline(stl_file, line); // Skip "outer loop"
                for (int i = 0; i < 3; i++) {
                    std::getline(stl_file, line); // Read vertex
                    std::istringstream sin(line.substr(line.find("vertex") + 6)); // Initialize with the part after "facet normal"
                    sin >> verteces[i];
                }
                std::getline(stl_file, line); // Skip "endloop"
                std::getline(stl_file, line); // Skip "endfacet"


                n = determineNormal(verteces[0], verteces[1], verteces[2]);
                Facet facet(n, verteces[0], verteces[1], verteces[2]);

                facets.push_back(facet);
            }

        }

        stl_file.close();

    }
    return facets;
}