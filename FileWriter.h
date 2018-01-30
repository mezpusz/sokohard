#pragma once

#include "Util.h"

class FileWriter
{
public:
    static bool writeMapToFile(vector<char> map, int width, int height, const string& filename, const string& solution);
    static vector<char> finalizeMap(vector<char> map, int width, int height);
};
