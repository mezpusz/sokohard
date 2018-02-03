#pragma once

#include <algorithm>

inline int Random(int first, int last)
{
    return std::rand() % (last-first) + first;
}
