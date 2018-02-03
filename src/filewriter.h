#pragma once

#include <string>
#include <vector>

class FileWriter
{
public:
    static bool writeMapToFile(std::vector<char> map, int width, int height, const std::string& filename, const std::string& solution);
    static std::vector<char> finalizeMap(std::vector<char> map, int width, int height);
};
