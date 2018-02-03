#include "filewriter.h"

#include <fstream>
#include <iostream>

bool FileWriter::writeMapToFile(std::vector<char> map, int width, int height, const std::string& filename, const std::string& solution)
{
    std::ofstream mapFile(filename + ".sok");
    std::ofstream solFile(filename + "_solution.sok");

    if(!mapFile.is_open() || !solFile.is_open())
    {
        return false;
    }

    std::cout << "Writing result map to file...";

    map = finalizeMap(map,width,height);

    width += 2;
    height += 2;

    for(int j = 0; j < height; ++j)
    {
        for(int i = 0; i < width; ++i)
        {
            mapFile << map[j*width + i];
        }
        mapFile << '\n';
    }
    mapFile << '\n';

    solFile << solution;
    solFile << '\n';

    std::cout << "completed!\n";
    mapFile.close();
    solFile.close();
    return true;
}

std::vector<char> FileWriter::finalizeMap(std::vector<char> v, int width, int height)
{
    std::vector<char> out;
    out.clear();

    for(int i = 0; i < width + 2; ++i)
    {
        out.push_back(' ');
    }
    for(int j = 0; j < height; ++j)
    {
        out.push_back(' ');
        for(int i = 0; i < width; ++i)
        {
            out.push_back(v[j*width + i]);
        }
        out.push_back(' ');
    }
    for(int i = 0; i < width + 2; ++i)
    {
        out.push_back(' ');
    }

    for(int i = 1; i <= width; ++i)
    {
        if(out[width + 2 + i] != '#')
        {
            out[i-1]	= '#';
            out[i]		= '#';
            out[i+1]	= '#';
        }
        if(out[(height)*(width + 2) + i] != '#')
        {
            out[(height+1)*(width + 2) + i-1]	= '#';
            out[(height+1)*(width + 2) + i]		= '#';
            out[(height+1)*(width + 2) + i+1]	= '#';
        }
    }

    for(int i = 1; i <= height; ++i)
    {
        if(out[i*(width + 2) + 1] != '#')
        {
            out[(i-1)*(width + 2)]	= '#';
            out[i*(width + 2)]		= '#';
            out[(i+1)*(width + 2)]	= '#';
        }
        if(out[i*(width + 2) + width] != '#')
        {
            out[(i-1)*(width + 2) + width + 1]	= '#';
            out[i*(width + 2) + width + 1]		= '#';
            out[(i+1)*(width + 2) + width + 1]	= '#';
        }
    }

    return out;
}
