#pragma once

#include "levelgenerator.h"

class LevelSolver
    : public LevelGenerator
{
public:
    LevelSolver(size_t w,
        size_t h,
        std::vector<char> v,
        std::set<Position> boxes,
        std::set<Position> goals,
        Position player);
    bool solve();

private:
    void storeSolution(State initial);

    std::set<Position> m_goals;
    State m_initialState;
};
