#pragma once

#include "Util.h"

class Map
{
public:
    Map() = default;

    void init(int width, int height, char c);
    void init(int width, int height, vector<char> in);

    char& operator()(int x, int y) const;
    char& operator()(int x, int y);
    char& operator()(Position p) const;
    char& operator()(Position p);
    vector<char>& getMap();
    vector<char>::iterator begin();
    vector<char>::iterator end();
    int width() const;
    int height() const;

    void printMap() const;

private:
    int m_width;
    int m_height;

    vector<char> m_map;
};
