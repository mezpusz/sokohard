#pragma once

#include "map.h"
#include "position.h"
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
    void placeBest();
    void printBest();
    void calculateSolution();
    std::string getSolution() const;
    size_t getMax() const;

private:
    std::vector<Position> initPlayer(std::set<Position> boxes);
    Position placePlayer(std::set<Position> boxes, Position prev);
    size_t floodfill(Position p, Position& min);
    void placeGoals();
    std::vector<State> expand(State s);
    
    static const Position direction[];

    size_t width; // x coordinate
    size_t height; // y coordinate
    size_t numBoxes;
    bool box_changes;
    size_t available;

    Map m_map;
    Map m_bestMap;
    State m_best;
    size_t m_max;
    std::vector<State> m_bestSolution;
    std::string m_solution;
    std::set<Position> m_bestGoals;

    std::set<Position> goals;

    // Not yet processed states
    std::deque<State> openSet;
    // Set to know which states have we encountered
    std::set<State> checked;
    // Processed states with their value
    std::map<State, size_t> closedSet;
    // Map to store each state's parent
    std::map<State, State> parents;
};
