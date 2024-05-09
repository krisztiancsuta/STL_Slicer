#include "STLFile.h"
#include "Facet.h"
#include "Vector.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Facet> STLFile::readSTLFile(const std::string& filename, const std::string& mode) {

    std::vector<Facet> facets; //letrehozok egy vektort amibe a facet-ek lesznek ez fog dinimaikusan novekedni

    if (mode == "binary")
    {
        std::ifstream stl_file(filename, std::ios::binary);
        if (!stl_file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
            return facets;
        }

        // Read the header (80 bytes) and ignore it
        stl_file.ignore(80);

        // Read the number of facets (4 bytes)
        uint32_t numFacets;
        stl_file.read(reinterpret_cast<char*>(&numFacets), sizeof(numFacets));

        // Read each facet
        for (uint32_t i = 0; i < numFacets; i++) {
            // Read the normal vector (12 bytes)
            float normal[3];
            stl_file.read(reinterpret_cast<char*>(&normal), sizeof(normal));

            // Read the vertices (36 bytes)
            Vector vertices[3];
            float xyz[3];
            for (int j = 0; j < 3; j++) {
                stl_file.read(reinterpret_cast<char*>(&xyz), sizeof(xyz));
                vertices[j].convert(xyz);
                if (vertices[j] < minZ) {
                    minZ >> vertices[j];
                }
                if (vertices[j] > maxZ) {
                    maxZ >> vertices[j];
                }
            }

            // Skip the attribute byte count (2 bytes)
            stl_file.ignore(2);

            Facet facet(vertices[0], vertices[1], vertices[2]);
            facets.push_back(facet);
        }

        stl_file.close();
    }
    else//Read file in text format
    {
        std::ifstream stl_file(filename);
        if (!stl_file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
            return facets;
        }

        std::string line;
        while (std::getline(stl_file, line)) { // beolvassa az elso sort
            Vector xyz[3];

            if (line.find("facet normal") != std::string::npos) {
                //
                //std::istringstream sin(line.substr(line.find("facet normal") + 12)); // Initialize with the part after "facet normal"
                //sin >> n; // overloaded >> operator
                std::getline(stl_file, line); // Skip "outer loop"
                for (int i = 0; i < 3; i++) {
                    std::getline(stl_file, line); // Read vertex
                    std::istringstream sin(line.substr(line.find("vertex") + 6)); // Initialize with the part after "facet normal"
                    sin >> xyz[i];
                    if (xyz[i] < minZ) {
                        minZ >> xyz[i];//"beletöltöm a Vector >> operatorral a koordinatat"
                    }
                    if (xyz[i] > maxZ) {
                        maxZ >> xyz[i];
                    }
                }
                std::getline(stl_file, line); // Skip "endloop"
                std::getline(stl_file, line); // Skip "endfacet"

                Facet facet(xyz[0], xyz[1], xyz[2]);

                facets.push_back(facet);
            }
        }
        stl_file.close();
    }
    return facets;
}

double STLFile::minZ = 0;
double STLFile::maxZ = 0;