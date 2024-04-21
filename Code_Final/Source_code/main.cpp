#include"Vector.h"
#include"Plane.h"
#include"Section.h"
#include"STLFile.h"
#include"Facet.h"
#include <iostream>
#include<vector>

int main() {

    try {
#if 0
        Vector v1(1, 0, 0);
        Vector v2(2, 1, 0);
        std::cout << Vector::dot(v1, v2) << std::endl;
        std::cout << Vector::cross(v1, v2) << std::endl;
        std::cout << v2 - v1 << std::endl;
        std::cout << v1.getLength();
#endif
        // 1) A facetek beolvasása. Bemenet az STL fájl, kimenet Facet-ek vektora.
        // ezután ciklusban
        std::vector<Facet> facets = STLFile::readSTLFile("gomb.stl", "text");
        double max = STLFile::maxZ;
        double min = STLFile::minZ;
        //Főciklus amiben 0.2 mm retegvastagsaggal szeletelunk
        for (double i = min; i < max; i = i + 0.2)
        {
            /* code */
        }

        // 2) szakaszok legyártása (nem egyenesek, szakaszok). Bementek:
        //    Facet-ek vektora, vágó sík. Kimenet: szakaszok vektora.

        // 3) (opcionális) szakaszok rendezése optimális bejáráshoz (csak
        //    gyorsítás, enélkül is nyomtatható)

        // 4) Gcode fájl egy rétegének legyártása


        return 0;
    }
    catch (char const* str) {
        std::cerr << "Caught exception: " << str << '\n';
    }


}

