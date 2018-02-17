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
    std::vector<Position> initPlayer(std::set<Position> boxes);
    Position placePlayer(std::set<Position> boxes, Position prev);
    size_t floodfill(Position p, Position& min);
    std::set<Position> placeGoals();

private:
    static const Position direction[];

    size_t width;
    size_t height;
    size_t numBoxes;
    size_t available;

    Map m_map;
//    std::set<Position> m_goals;
};
