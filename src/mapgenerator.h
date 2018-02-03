#pragma once

#include "pattern.h"
#include "position.h"
#include "map.h"

#include <set>
#include <string>
#include <vector>

class MapGenerator
{
public:
    MapGenerator(int w, int h, int m, int n, int num);
    bool generate();
    std::vector<char>& getMap();
    void printMap() const;

private:
    void setCharMap(Pattern& p, int i, int j);
    bool isConnected();
    bool checkForOpenSections();
    bool checkForDeadEnds();
    int countConnected(int i, int j);

    int width;
    int height;
    int m, n;
    int numBoxes;

    std::set<Pattern> patterns;
    Map charMap;
    std::vector<Pattern> patternMap;
};
