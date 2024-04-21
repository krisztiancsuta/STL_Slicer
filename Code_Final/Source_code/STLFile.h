#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Facet.h"

class STLFile
{
public:
    static std::vector<Facet> readSTLFile(const std::string& filename, const std::string& mode);

};