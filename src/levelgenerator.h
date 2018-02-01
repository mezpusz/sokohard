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
    LevelGenerator(int w, int h, int n);
    int generate(std::vector<char> v);
    std::vector<char>& getMap();
    void printMap() const;
    void placeBest();
    void printBest();
    void calculateSolution();
    std::string getSolution() const;
    int getMax() const;

private:
    std::vector<Position> initPlayer(std::set<Position> boxes);
    Position placePlayer(std::set<Position> boxes, Position prev);
    int floodfill(Position p, Position& min);
    void placeGoals();
    std::vector<State> expand(State s);
    
    static const Position direction[];

    int width; // x coordinate
    int height; // y coordinate
    int numBoxes;
    int available;

    Map m_map;
    Map m_bestMap;
    State m_best;
    int m_max;
    std::vector<State> m_bestSolution;
    std::string m_solution;
    std::set<Position> m_bestGoals;

    std::set<Position> goals;

    std::deque<State> openSet;
    std::set<State> checked;
    std::map<State, int> closedSet;
    std::map<State, State> parents;
};
