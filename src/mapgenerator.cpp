#include "mapgenerator.h"

#include "map_elements.h"
#include "patterns_list.h"
#include "util.h"

#include <iostream>

MapGenerator::MapGenerator(int w, int h, int m, int n, int num)
    : width(w)
    , height(h)
    , m(m)
    , n(n)
    , numBoxes(num)
    , patterns()
{
    for (const auto& pattern : patterns_list_3x3)
    {
        Pattern pat, p1;
        pat.Initialize(n,m,pattern);

        for (int r = Rotation::_0; r != Rotation::_270; ++r)
        {
            patterns.insert(pat.getPattern(static_cast<Rotation>(r), false));
            patterns.insert(pat.getPattern(static_cast<Rotation>(r), true));
        }
    }
}

bool MapGenerator::generate()
{
    bool match;

    int numPatterns = patterns.size();
    int ptry;

    charMap.init(width*m, height*n, '0');
    patternMap.resize(width*height);

    do
    {
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                Pattern p;
                ptry = 0;

                do
                {
                    auto it = patterns.begin();
                    advance(it, Random(0, numPatterns-1));
                    p = *it;

                    if ((i > 0 && j > 0 && !p.match(patternMap[(j-1)*width + i - 1], NORTH_WEST))
                        || (j > 0 && !p.match(patternMap[(j-1)*width + i], NORTH))
                        || (i < (width - 1) && j > 0 && !p.match(patternMap[(j-1)*width + i + 1], NORTH_EAST))
                        || (i > 0 && !p.match(patternMap[j*width + i - 1], WEST)))
                    {
                        match = false;
                    }
                    else
                    {
                        match = true;
                    }

                    if (++ptry > 100)
                    {
                        return false;
                    }
                }
                while(!match);

                patternMap[j*width + i] = p;
                setCharMap(p, i, j);
            }
        }
    } 
    while(!isConnected() || checkForOpenSections());

    checkForDeadEnds();
    //printMap();

    return true;
}

std::vector<char>& MapGenerator::getMap()
{
    return charMap.getMap();
}

void MapGenerator::setCharMap(Pattern& p, int i, int j)
{
    std::vector<char> v = p.getPatternAsVector();
    for (int k = 0; k < m; ++k)
    {
        for (int l = 0; l < n; ++l)
        {
            charMap(m*i + k, n*j + l) = v[(l+1)*(m+2) + k + 1];
        }
    }
}

bool MapGenerator::isConnected()
{
    int floors = 0;

    Map tempMap = charMap;

    for(int i = 0; i < width*m; ++i)
    {
        for(int j = 0; j < height*n; ++j)
        {
            if(charMap(i,j) == EMPTY) floors++;
        }
    }

    // Sanity check so that we don't end up with a map too small
    if (floors < numBoxes + 2)
    {
        return false;
    }

    int result = 0;
    for (int i = 0; i < width*m; ++i)
    {
        for (int j = 0; j < height*n; ++j)
        {
            if (charMap(i,j) == EMPTY)
            {
                result = countConnected(i,j);
                break;
            }
        }
        if(result > 0) break;
    }

    charMap = tempMap;

    return (floors == result) && (floors > 0);
}

int MapGenerator::countConnected(int i, int j)
{
    int result = 0;
    if(charMap(i,j) == EMPTY)
    {
        charMap(i,j) = '_';
        result++;

        if (i > 0)
        {
            result += countConnected(i-1, j);
        }
        if (i < width*m)
        {
            result += countConnected(i+1, j);
        }
        if (j > 0)
        {
            result += countConnected(i, j-1);
        }
        if (j < height*n)
        {
            result += countConnected(i, j+1);
        }
    }
    return result;
}

bool MapGenerator::checkForOpenSections()
{
    int x = 0, y = 0;

    for(int i = 0; i < width*m; ++i)
    {
        for(int j = 0; j < height*n; ++j)
        {
            if(charMap(i,j) == EMPTY && i + 4 <= width*m && j + 3 <= height*n)
            {
                for(int k = i; k < i + 4; ++k)
                {
                    for(int l = j; l < j + 3; ++l)
                    {
                        if(charMap(k,l) == EMPTY) y++;
                        else break;
                    }
                    if(y >= 3) x++;
                    y = 0;
                }
                if(x >= 4)
                {
                    return true;
                }
                x = 0;
            }
            if(charMap(i,j) == EMPTY && i + 3 <= width*m && j + 4 <= height*n)
            {
                for(int k = i; k < i + 3; ++k)
                {
                    for(int l = j; l < j + 4; ++l)
                    {
                        if(charMap(k,l) == EMPTY) y++;
                        else break;
                    }

                    if(y >= 4) x++;
                    y = 0;
                }
                if(x >= 3)
                {
                    return true;
                }
                x = 0;
            }
        }
    }
    return false;
}

void MapGenerator::checkForDeadEnds()
{
    for(int i = 0; i < width*m; ++i)
    {
        for(int j = 0; j < height*n; ++j)
        {
            if (charMap(i,j) == WALL)
            {
                continue;
            }

            bool north = (j-1 < 0 || (charMap(i,j-1) == WALL));
            bool south = (j+1 >= height*n || (charMap(i,j+1) == WALL));
            bool west = (i-1 < 0 || (charMap(i-1,j) == WALL));
            bool east = (i+1 >= width*m || (charMap(i+1,j) == WALL));

            if ((north && south && (west || east))
                || (west && east && (north || south)))
            {
                removeDeadEnd(i, j);
            }
        }
    }
}

void MapGenerator::removeDeadEnd(int i, int j)
{
    bool north = (j-1 < 0 || (charMap(i,j-1) == WALL));
    bool south = (j+1 >= height*n || (charMap(i,j+1) == WALL));
    bool west = (i-1 < 0 || (charMap(i-1,j) == WALL));
    bool east = (i+1 >= width*m || (charMap(i+1,j) == WALL));

    if (north && south)
    {
        if (west)
        {
            charMap(i, j) = WALL;
            removeDeadEnd(i+1, j);
        }
        else if (east)
        {
            charMap(i, j) = WALL;
            removeDeadEnd(i-1, j);
        }
    }
    else if (west && east)
    {
        if (north)
        {
            charMap(i, j) = WALL;
            removeDeadEnd(i, j+1);
        }
        else if (south)
        {
            charMap(i, j) = WALL;
            removeDeadEnd(i, j-1);
        }
    }
}

void MapGenerator::printMap() const
{
    std::cout << charMap;
}
