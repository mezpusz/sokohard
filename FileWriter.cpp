#include "FileWriter.h"

bool FileWriter::writeMapToFile(vector<char> map, int width, int height, const string& filename, const string& solution)
{
    ofstream mapFile(filename + ".sok");
    ofstream solFile(filename + "_solution.sok");

    if(!mapFile.is_open() || !solFile.is_open())
    {
        return false;
    }

    cout << "Writing result map to file...";

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

    cout << "completed!\n";
    mapFile.close();
    solFile.close();
    return true;
}

vector<char> FileWriter::finalizeMap(vector<char> v, int width, int height)
{
    vector<char> out;
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
