#pragma once

#include "map.h"
#include "position.h"
#include "state.h"

#include <set>
#include <string>
#include <vector>

class SolutionHandler
{
public:
    SolutionHandler();
    void update(Map map, std::set<Position> goals, std::vector<State> states);
    Map placeBest();
    void printBest();
    std::string calculateSolution();

private:
    Map m_map;
    std::set<Position> m_goals;
    std::vector<State> m_states;
};
