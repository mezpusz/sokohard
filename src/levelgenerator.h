#pragma once

#include "map.h"
#include "position.h"
#include "positionselector.h"
#include "solutionhandler.h"
#include "state.h"

#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>

class LevelGenerator
{
public:
    LevelGenerator(size_t w, size_t h, size_t n, bool box_changes);
    size_t generate(std::vector<char> v);
    std::vector<char>& getMap();
    void printMap() const;
    Map placeBest();
    void printBest();
    void calculateSolution();
    std::string getSolution() const;
    size_t getMax() const;

protected:
    size_t updateBest(std::set<Position> goals);
    size_t floodfill(Position p, Position& min);
    std::vector<State> expand(State s);

    size_t m_width;
    size_t m_height;
    bool m_boxChanges;
    PositionSelector m_positionSelector;
    SolutionHandler m_solutionHandler;

    Map m_map;
    size_t m_max;
    std::string m_solution;

    // Not yet processed states
    std::deque<State> m_openSet;
    // Processed states with their value
    std::map<State, size_t> m_closedSet;
    // Map to store each state's parent
    std::map<State, State> m_parents;
};
