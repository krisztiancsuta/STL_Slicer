#include "Vector.h"
#include "Plane.h"
#include "Section.h"
#include "STLFile.h"
#include "Facet.h"
#include <iostream>
#include <vector>
#include "Gcode.h"
#include <fstream>
#include <cmath>

#define DEBUG false

/**
 * @brief The main function of the program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <layer resolution> (in mm)\n Example: ./main test.stl 0.2";
        return 1;
    }
    try
    {
        double layerres = std::stod(argv[2]);
#if DEBUG
        Vector v1(1, 0, 0);
        Vector v2(2, 1, 0);
        std::cout << Vector::dot(v1, v2) << std::endl;
        std::cout << Vector::cross(v1, v2) << std::endl;
        std::cout << v2 - v1 << std::endl;
        std::cout << v1.getLength();

        Plane cutter(Vector(0, 0, 1), Vector(0, 0, 1));
        Section szakasz(Vector(0, 0, 1), Vector(0, 0, 2));
        Vector p = szakasz.PlaneInterSection(cutter);
#elif !DEBUG
        // 1) Read facets from an STL file. Input: STL file, Output: vector of Facets.
        //    Then in a loop:
        std::vector<Facet> facets = STLFile::readSTLFile(argv[1]);
        double max = STLFile::maxZ;
        double min = STLFile::minZ;

        std::string filename = std::string(argv[1]);
        size_t dotPos = filename.find_last_of(".");
        if (dotPos != std::string::npos) {
            filename = filename.substr(0, dotPos);
        }
        filename += ".gcode";

        // Open gcode and write starting lines into it.
        std::ofstream gcode(filename);
        if (gcode.fail())
            throw std::runtime_error("Error writing file: " + filename + ".gcode");
        Gcode::StartGcode(gcode);

        std::cout << "Slicing: " << argv[1] << std::endl;
        std::cout << "Progress:     ";
        for (double i = min; i <= max; i = i + layerres)
        {
            Plane cutter(Vector(0, 0, i), Vector(0, 0, 1));
            std::vector<Section> sections_per_level;

            // Calculate the percentage and convert it to a string
            int percentage = std::ceil((i / static_cast<double>(max)) * 100);
            std::string percentageStr = std::to_string(percentage) + "%";

            // Calculate the number of characters to delete
            int charsToDelete = percentageStr.length();

            // Print backspaces to delete the previous percentage output
            for (int j = 0; j < charsToDelete; ++j) {
                std::cout << '\b';
            }

            // Print the new percentage
            std::cout << percentageStr << std::flush;


            // 2) Generate sections (not straight lines, but sections) from facets and cutting plane. Inputs:
            //    vector of Facets, cutting plane. Output: vector of Sections.
            for (unsigned j = 0; j < facets.size(); j++)
            {
                bool isValidSection = true;

                Section tmp = facets[j].PlaneIntersection(cutter, isValidSection);

                if (isValidSection)
                {
                    // std::cout << "\t" << facets[j] << std::endl;
                    // std::cout << "\t\t" << tmp << std::endl;
                    sections_per_level.push_back(tmp);
                }
            }

            // 3)Sort sections for optimal traversal (only for speed, it is printable without sorting)
            Gcode::SortSections(sections_per_level);
            /*
            for (unsigned i = 0; i < sections_per_level.size(); i++)
            {
                std::cout << "\t" << sections_per_level[i] << std::endl;
            }
            */

            // 4) Generate gcode for one layer
            Gcode::WriteGcode(gcode, sections_per_level);
        }

        Gcode::CloseGcode(gcode);

#endif
        return 0;
    }
    catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument please enter a valid double value!" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <filename> <layer resolution> (in mm)" << std::endl << "Example: ./main test.stl 0.2";
    }
    catch (const std::exception& exc)
    {
        std::cerr << "Caught exception: " << exc.what() << '\n';
    }
}
