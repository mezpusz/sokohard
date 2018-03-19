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

    m_closedSet.clear();
    parents.clear();
    openSet.clear();

    auto goals = positionSelector.placeGoals();
    const auto playerPositions = positionSelector.initPlayer(goals);

    for (const auto& p : playerPositions)
    {
        State state(p, goals, 0);
        openSet.push_back(state);
        m_closedSet.insert(std::pair<State, size_t>(state, 0));
    }

    while(!openSet.empty())
    {
        const State current = openSet.front();
        openSet.pop_front();

        auto states = expand(current);
        for(const auto& s : states)
        {
            if (m_closedSet.count(s) == 0)
            {
                openSet.push_back(s);
                size_t pValue = 0;
                pValue = m_closedSet.find(current)->second;
                pValue += box_changes ? s.getBoxChange() : 1;
                m_closedSet.insert(std::pair<State, size_t>(s, pValue));
                parents.insert(std::pair<State, State>(s, current));
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
        while(parents.find(t) != parents.end())
        {
            states.push_back(parents.find(t)->second);
            t = parents.find(t)->second;
        }
        solutionHandler.update(m_map, goals, states);
    }
    return max;
}

std::vector<char>& LevelGenerator::getMap()
{
    return m_map.getMap();
}

std::vector<State> LevelGenerator::expand(const State s)
{
    std::vector<State> result;
    const Position min(0,0);
    const Position max(width, height);

    std::set<Position> playerPos = s.getPlayer();
    std::set<Position> boxes = s.getBoxes();

    for(const auto& p : playerPos)
    {
        Position actual;

        for(const auto& d : directions)
        {
            actual = p;

            if (actual.isInInterval(min,max,d)
                && boxes.count(actual + d) != 0)
            {
                auto direction = d.inv();
                auto box = actual + d;
                
                while (actual.isInInterval(min,max,direction)
                    && m_map(actual + direction) == EMPTY)
                {
                    std::set<Position> ps(boxes.begin(), boxes.end());
                    auto pushedBox = *(ps.find(box));
                    ps.erase(pushedBox);
                    ps.insert(actual);
                    std::set<Position> newPlayer = positionSelector.placePlayer(ps, actual + direction);
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

size_t LevelGenerator::getMax() const
{
    return m_max;
}

std::string LevelGenerator::getSolution() const
{
    return m_solution;
}
