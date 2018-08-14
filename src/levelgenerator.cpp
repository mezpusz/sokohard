#include "levelgenerator.h"

#include "map_elements.h"
#include "util.h"

#include <iostream>

LevelGenerator::LevelGenerator(size_t w, size_t h, size_t n, bool box_changes)
    : m_width(w)
    , m_height(h)
    , m_boxChanges(box_changes)
    , m_positionSelector(w, h, n)
    , m_solutionHandler()
    , m_map()
    , m_max(0)
    , m_solution()
    , m_openSet()
    , m_closedSet()
    , m_parents()
{
}

size_t LevelGenerator::generate(std::vector<char> v)
{
    m_positionSelector.init(v);
    m_map.init(m_width, m_height, v);

    m_closedSet.clear();
    m_parents.clear();
    m_openSet.clear();

    auto goals = m_positionSelector.placeGoals();
    const auto playerPositions = m_positionSelector.initPlayer(goals);

    for (const auto& p : playerPositions)
    {
        State state(p, goals, 0);
        m_openSet.push_back(state);
        m_closedSet.insert(std::pair<State, size_t>(state, 0));
    }

    while(!m_openSet.empty())
    {
        const State current = m_openSet.front();
        m_openSet.pop_front();

        auto states = expand(current);
        for(const auto& s : states)
        {
            if (m_closedSet.count(s) == 0)
            {
                m_openSet.push_back(s);
                size_t pValue = 0;
                pValue = m_closedSet.find(current)->second;
                pValue += m_boxChanges ? s.getBoxChange() : 1;
                m_closedSet.insert(std::pair<State, size_t>(s, pValue));
                m_parents.insert(std::pair<State, State>(s, current));
            }
        }
    }

    return updateBest(goals);
}

size_t LevelGenerator::updateBest(std::set<Position> goals)
{
    size_t max = 0;
    State best;

    for(const auto& [state,value] : m_closedSet)
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
        while(m_parents.find(t) != m_parents.end())
        {
            states.push_back(m_parents.find(t)->second);
            t = m_parents.find(t)->second;
        }
        m_solutionHandler.update(m_map, goals, states);
    }
    return max;
}

size_t LevelGenerator::floodfill(Position p, Position& min)
{
    if (p.x < 0 || p.x >= m_width
        || p.y < 0 || p.y >= m_height
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

std::vector<State> LevelGenerator::expand(const State s)
{
    std::vector<State> result;
    const Position min(0,0);
    const Position max(m_width, m_height);

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

        for(const auto& direction : directions)
        {
            if (box.isInInterval(min,max,direction)
                && floodedMap(box + direction) == '_')
            {
                actual = box;
                actual += direction;

                while (actual.isInInterval(min,max,direction)
                    && floodedMap(actual + direction) == '_')
                {
                    std::set<Position> ps(boxes.begin(), boxes.end());
                    auto pushedBox = *(ps.find(box));
                    ps.erase(pushedBox);
                    ps.insert(actual);
                    Position newPlayer = m_positionSelector.placePlayer(ps, actual + direction);
                    result.push_back(State(newPlayer, ps, pushedBox.diff(actual).abs()));
                    actual += direction;
                }
            }
        }
    }
    return result;
}

void LevelGenerator::calculateSolution()
{
    m_solution = m_solutionHandler.calculateSolution();
}

Map LevelGenerator::placeBest()
{
    return m_solutionHandler.placeBest();
}

void LevelGenerator::printBest()
{
    m_solutionHandler.printBest();
}

void LevelGenerator::printMap() const
{
    std::cout << m_map;
}

size_t LevelGenerator::getMax() const
{
    return m_max;
}

std::string LevelGenerator::getSolution() const
{
    return m_solution;
}
