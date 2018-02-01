#pragma once

#include "position.h"

#include <ostream>
#include <vector>

class Map
{
public:
    Map() = default;

    void init(int width, int height, char c);
    void init(int width, int height, std::vector<char> in);

    char& operator()(int x, int y) const;
    char& operator()(int x, int y);
    char& operator()(Position p) const;
    char& operator()(Position p);
    std::vector<char>& getMap();
    std::vector<char>::iterator begin();
    std::vector<char>::iterator end();
    int width() const;
    int height() const;

    friend std::ostream& operator<<(std::ostream& os, const Map& map);

private:
    int m_width;
    int m_height;

    std::vector<char> m_map;
};

std::ostream& operator<<(std::ostream& os, const Map& map);
