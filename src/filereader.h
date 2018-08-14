#pragma once

#include "position.h"

#include <set>
#include <vector>

class FileReader
{
public:
    static bool parseMap(const std::string& filename,
                         size_t& width, size_t& height,
                         std::vector<char>& map,
                         Position& player,
                         std::set<Position>& goals,
                         std::set<Position>& boxes);
};
