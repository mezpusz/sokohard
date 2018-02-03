#pragma once

#include <algorithm>

enum Rotation
{
    _0,
    _90,
    _180,
    _270
};

/*
 * NORTH_WEST | NORTH | NORTH_EAST
 * -----------*********-----------
 *    WEST    *pattern*   EAST
 * -----------*********-----------
 * SOUTH_WEST | SOUTH | SOUTH_EAST
 */
enum Join
{
    NORTH = 0x1,
    EAST = 0x2,
    SOUTH = 0x4,
    WEST = 0x8,
    NORTH_EAST = NORTH | EAST,
    SOUTH_EAST = SOUTH | EAST,
    SOUTH_WEST = SOUTH | WEST,
    NORTH_WEST = NORTH | WEST
};

inline int Random(int first, int last)
{
    return std::rand() % (last-first) + first;
}
