#include "Vector.h"
#include "Plane.h"
#include "Section.h"
#include "STLFile.h"
#include "Facet.h"
#include <iostream>
#include <vector>
#include "Gcode.h"
#include <fstream>

#define DEBUG false
int main()
{

    try
    {
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
        // 1) A facetek beolvasása. Bemenet az STL fájl, kimenet Facet-ek vektora.
        // ezután ciklusban
        std::vector<Facet> facets = STLFile::readSTLFile("yoda.stl", "text");
        double max = STLFile::maxZ;
        double min = STLFile::minZ;
        // Főciklus amiben 0.2 mm retegvastagsaggal szeletelunk

        std::ofstream gcode("Generated.gcode");
        if (gcode.fail())
            throw std::runtime_error("Error writing file: Generated.gcode");
        std::string start = "G28;Home\nG1 Z20 F6000;Move the platform down 20mm\n";
        std::string stop = "G28 X0 Y0;";
        gcode << start << std::endl;

        for (double i = min; i <= max; i = i + 0.2)
        {
            Plane cutter(Vector(0, 0, i), Vector(0, 0, 1));
            std::vector<Section> sections_per_level;
            std::cout << "Level " << i << " mm" << std::endl;
            for (unsigned j = 0; j < facets.size(); j++)
            {
                bool isValidSection = true;
                // 2) szakaszok legyártása (nem egyenesek, szakaszok). Bementek:
                //    Facet-ek vektora, vágó sík. Kimenet: szakaszok vektora.

                Section tmp = facets[j].PlaneIntersection(cutter, isValidSection);

                if (isValidSection)
                {
                    // std::cout << "\t" << facets[j] << std::endl;
                    // std::cout << "\t\t" << tmp << std::endl;
                    sections_per_level.push_back(tmp);
                }
            }

            // 3) (opcionális) szakaszok rendezése optimális bejáráshoz (csak
            //    gyorsítás, enélkül is nyomtatható)
            Gcode::SortSections(sections_per_level);
            /*
            for (unsigned i = 0; i < sections_per_level.size(); i++)
            {
                std::cout << "\t" << sections_per_level[i] << std::endl;
            }
            */

            // 4) Gcode fájl egy rétegének legyártása
            Gcode::WriteGcode(gcode, sections_per_level);
        }
        gcode << stop << std::endl;

        getchar();
#endif
        return 0;
    }
    catch (const std::exception& exc)
    {
        std::cerr << "Caught exception: " << exc.what() << '\n';
    }
}
