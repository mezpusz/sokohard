#pragma once

#include "Pattern.h"
#include "Map.h"
#include "Util.h"

class MapGenerator
{
public:
    MapGenerator(int w, int h, int m, int n, int num);
    bool loadPatterns(const string& filename);
    bool generate();
    vector<char>& getMap();
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

    set<Pattern> patterns;
    Map charMap;
    vector<Pattern> patternMap;
};
