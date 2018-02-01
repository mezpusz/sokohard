#pragma once

#include <vector>
#include <set>
#include <deque>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

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
    return rand() % (last-first) + first;
}
