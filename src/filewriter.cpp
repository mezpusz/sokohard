#include "filewriter.h"

#include "map_elements.h"

#include <fstream>
#include <iostream>

bool FileWriter::writeMapToFile(std::vector<char> map, size_t width, size_t height, const std::string& filename, const std::string& solution)
{
    std::ofstream mapFile(filename + ".sok");
    std::ofstream solFile(filename + "_solution.sok");

    if(!mapFile.is_open() || !solFile.is_open())
    {
        return false;
    }

    map = finalizeMap(map,width,height);

    width += 2;
    height += 2;

    for(size_t j = 0; j < height; ++j)
    {
        for(size_t i = 0; i < width; ++i)
        {
            mapFile << map[j*width + i];
        }
        mapFile << std::endl;
    }

    solFile << solution << std::endl;

    mapFile.close();
    solFile.close();
    return true;
}

std::vector<char> FileWriter::finalizeMap(std::vector<char> v, size_t width, size_t height)
{
    std::vector<char> out;
    out.clear();

    for(size_t i = 0; i < width + 2; ++i)
    {
        out.push_back(EMPTY);
    }
    for(size_t j = 0; j < height; ++j)
    {
        out.push_back(EMPTY);
        for(size_t i = 0; i < width; ++i)
        {
            out.push_back(v[j*width + i]);
        }
        out.push_back(EMPTY);
    }
    for(size_t i = 0; i < width + 2; ++i)
    {
        out.push_back(EMPTY);
    }

    for(size_t i = 1; i <= width; ++i)
    {
        if(out[width + 2 + i] != WALL)
        {
            out[i-1]	= WALL;
            out[i]		= WALL;
            out[i+1]	= WALL;
        }
        if(out[(height)*(width + 2) + i] != WALL)
        {
            out[(height+1)*(width + 2) + i-1]	= WALL;
            out[(height+1)*(width + 2) + i]		= WALL;
            out[(height+1)*(width + 2) + i+1]	= WALL;
        }
    }

    for(size_t i = 1; i <= height; ++i)
    {
        if(out[i*(width + 2) + 1] != WALL)
        {
            out[(i-1)*(width + 2)]	= WALL;
            out[i*(width + 2)]		= WALL;
            out[(i+1)*(width + 2)]	= WALL;
        }
        if(out[i*(width + 2) + width] != WALL)
        {
            out[(i-1)*(width + 2) + width + 1]	= WALL;
            out[i*(width + 2) + width + 1]		= WALL;
            out[(i+1)*(width + 2) + width + 1]	= WALL;
        }
    }

    return out;
}
