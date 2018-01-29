#pragma once

#include "Pattern.h"
#include "Map.h"
#include "Util.h"

class MapGenerator
{

private:

    int width;
    int height;
    int m, n;
    int numBoxes;
    int bCount;

    set<Pattern> patterns;
    Map charMap;
    vector<Pattern> patternMap;

private:

    void setCharMap(Pattern& p, int i, int j);
    bool isConnected();
    bool checkForOpenSections();
    bool checkForDeadEnds();
    void dfs(int i, int j);

public:

    MapGenerator(int w, int h, int m, int n, int num);
    bool loadPatterns(const string& filename);
    bool generate();
    vector<char>& getMap();
    void printMap() const;
};
