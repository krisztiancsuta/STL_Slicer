#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Facet.h"


class STLFile
{
public:
    static double minZ;
    static double maxZ;
    static std::vector<Facet> readSTLFile(const std::string& filename);
    bool static isBinarySTL(const std::string& filename);

};