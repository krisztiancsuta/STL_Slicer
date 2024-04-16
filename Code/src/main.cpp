
#include <cstdlib>
#include <cstdio>
#include <float.h>
#include <math.h>
#include "modules.h"

int main(int argc, char const* argv[])
{
    /*

    //sik1
    STL::Point p1(1.0, 1.0, 0.0);
    STL::Point p2(1.0, -1.0, 1.0);
    STL::Point p3(1.0, 1.0, 2.0);
    STL::Vector n(1.0, 0.0, 0.0);
    STL::Facet f1(n, p1, p2, p3);

    //sik2
    STL::Point _p1(1.0, 1.0, 0);
    STL::Point _p2(-1.0, 1.0, 0.0);
    STL::Point _p3(-1.0, 1.0, 2.0);
    STL::Vector _n(1, 0, 0);
    STL::Facet f2(_n, _p1, _p2, _p3);
    double x = f2.getMinZ();
    int i = STL::check_neighbour(f1, f2);

    //vago sik
    STL::Vector nc(0.0, 0.0, 1);
    STL::Point pc(0.0, 0.0, 0.999);
    STL::Cutter cutter_plane(nc, pc);

    STL::Line test(STL::Vector(6.68, -6.64, 0), STL::Point(-5.68, 1, 1));
    STL::Line res1 = STL::faceIntersection(f1, cutter_plane);
    STL::Line res2 = STL::faceIntersection(f2, cutter_plane);

    res1.print();
    res2.print();

    STL::Point intP = STL::lineIntersection(res1, test);
    intP.print();
    STL::Point intP2 = STL::lineIntersection(res2, test);
    intP2.print();
    */

    std::vector<STL::Facet> facets = STL::read_STL("kocka.stl", "text");
    STL::generate_Id(facets);
    for (const auto& facet : facets) {
        facet.print();
    }
    std::vector<STL::Line> lines = STL::generate_Lines(facets);
    for (const auto& line : lines) {
        line.print();
    }
    std::vector<STL::Point> points = STL::generate_Points(lines);
    //TODO: forgasszog alapjan a pontokat rendezni

/*
Lines Done
Point: (0, 0, 0)
Direction Vector: (0, 0.894427, -0)
Id:467

Point: (10, 0, 0)
Direction Vector: (0, 0.894427, -0)
Id:289

Point: (0, 0, 0)
Direction Vector: (-0.894427, 0, 0)
Id:368

Point: (0, 10, 0)
Direction Vector: (-0.894427, -0, 0)
Id:579

for (const auto& line : lines) {
    line.print();
}
*/


    STL::write_gcode(points);
    return 0;
}
