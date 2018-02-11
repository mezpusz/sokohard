#pragma once

#include <string>
#include <vector>

class FileWriter
{
public:
    static bool writeMapToFile(std::vector<char> map, size_t width, size_t height, const std::string& filename, const std::string& solution);
    static std::vector<char> finalizeMap(std::vector<char> map, size_t width, size_t height);
};
