#include "levelgenerator.h"

#include "map_elements.h"
#include "util.h"

#include <iostream>

LevelGenerator::LevelGenerator(size_t w, size_t h, size_t n, bool box_changes)
    : width(w)
    , height(h)
    , box_changes(box_changes)
    , positionSelector(w, h, n)
    , solutionHandler()
    , m_max(0)
{
}

size_t LevelGenerator::generate(std::vector<char> v)
{
    positionSelector.init(v);
    m_map.init(width, height, v);

    closedSet.clear();
    parents.clear();
    openSet.clear();
    checked.clear();

    auto goals = positionSelector.placeGoals();
    const auto playerPositions = positionSelector.initPlayer(goals);

    for (const auto& p : playerPositions)
    {
        openSet.push_back(State(p, goals, 0));
        checked.insert(State(p, goals, 0));
    }

    while(!openSet.empty())
    {
        State current = openSet.front();
        openSet.pop_front();

        auto it = parents.find(current);
        if (it == parents.end())
        {
            closedSet.insert(std::pair<State, size_t>(current, 0));
        }
        else
        {
            State child = it->first;
            State parent = it->second;
            size_t pValue = closedSet.find(parent)->second;
            pValue += box_changes ? child.getBoxChange() : 1;
            closedSet.insert(std::pair<State, size_t>(current, pValue));
        }

        auto states = expand(current);
        for(const auto& s : states)
        {
            if (checked.count(s) == 0)
            {
                openSet.push_back(s);
                checked.insert(s);
                parents.insert(std::pair<State, State>(s, current));
            }
        }
    }

    size_t max = 0;
    State best;

    for(const auto& [state,value] : closedSet)
    {
        if(value >= max)
        {
            max = value;
            best = state;
        }
    }

    if(m_max < max)
    {
        m_max = max;
        State t = best;
        std::vector<State> states;
        states.push_back(best);
        while(parents.find(t) != parents.end())
        {
            states.push_back(parents.find(t)->second);
            t = parents.find(t)->second;
        }
        solutionHandler.init(m_map, goals, states);
    }

    return max;
}

size_t LevelGenerator::floodfill(Position p, Position& min)
{
    if (p.x < 0 || p.x >= width
        || p.y < 0 || p.y >= height
        || m_map(p) != EMPTY)
    {
        return 0;
    }
    
    size_t c = 1;
    if (p < min)
    {
        min = p;
    }

    m_map(p) = '_';

    c += floodfill(Position(p.x + 1, p.y), min);
    c += floodfill(Position(p.x - 1, p.y), min);
    c += floodfill(Position(p.x, p.y + 1), min);
    c += floodfill(Position(p.x, p.y - 1), min);

    return c;
}

std::vector<char>& LevelGenerator::getMap()
{
    return m_map.getMap();
}

std::vector<State> LevelGenerator::expand(State s)
{
    std::vector<State> result;
    const Position min(0,0);
    const Position max(width, height);

    Map tempMap = m_map;

    Position minPos = s.getPlayer();
    std::set<Position> boxes = s.getBoxes();
    for(const auto& b : boxes)
    {
        m_map(b) = BOX;
    }
    floodfill(s.getPlayer(), minPos);

    Map floodedMap = m_map;
    m_map = tempMap;

    for(const auto& box : boxes)
    {
        Position actual;

        for(size_t i = 0; i < 4; ++i)
        {
            if (box.isInInterval(min,max,direction[i])
                && floodedMap(box + direction[i]) == '_')
            {
                actual = box;
                actual += direction[i];

                while (actual.isInInterval(min,max,direction[i])
                    && floodedMap(actual + direction[i]) == '_')
                {
                    std::set<Position> ps(boxes.begin(), boxes.end());
                    auto pushedBox = *(ps.find(box));
                    ps.erase(pushedBox);
                    ps.insert(actual);
                    Position newPlayer = positionSelector.placePlayer(ps, actual + direction[i]);
                    result.push_back(State(newPlayer, ps, pushedBox.diff(actual).abs()));
                    actual += direction[i];
                }
            }
        }
    }
    return result;
}

void LevelGenerator::calculateSolution()
{
    m_solution = solutionHandler.calculateSolution();
}

Map LevelGenerator::placeBest()
{
    return solutionHandler.placeBest();
}

void LevelGenerator::printBest()
{
    solutionHandler.printBest();
}

void LevelGenerator::printMap() const
{
    std::cout << m_map;
}

std::string LevelGenerator::getSolution() const
{
    return m_solution;
}
