#pragma once

#include "map.h"

class FileWriter
{
public:
    static bool writeMapToFile(Map map, const std::string& filename);
    static bool writeSolutionToFile(const std::string& solution, const std::string& filename);
    static std::vector<char> finalizeMap(std::vector<char> map, size_t width, size_t height);
};
