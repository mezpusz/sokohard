#pragma once

#include "map.h"
#include "position.h"
#include "state.h"

#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>

class PositionSelector
{
public:
    PositionSelector(size_t width, size_t height, size_t boxNum);
    void init(std::vector<char> v);
    std::vector<std::set<Position>> initPlayer(std::set<Position> boxes);
    std::set<Position> placePlayer(std::set<Position> boxes, Position prev);
    size_t floodfill(Position p, Position& min);
    std::set<Position> placeGoals();

private:
    size_t width;
    size_t height;
    size_t numBoxes;
    size_t available;

    Map m_map;
//    std::set<Position> m_goals;
};
