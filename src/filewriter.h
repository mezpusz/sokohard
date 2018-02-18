#pragma once

#include "map.h"

class FileWriter
{
public:
    static bool writeMapToFile(Map map, const std::string& filename, const std::string& solution);
    static std::vector<char> finalizeMap(std::vector<char> map, size_t width, size_t height);
};
