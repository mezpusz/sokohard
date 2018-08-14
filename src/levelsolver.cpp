#include "levelsolver.h"

#include "map_elements.h"
#include "util.h"

#include <iostream>

LevelSolver::LevelSolver(size_t w,
        size_t h,
        std::vector<char> v,
        std::set<Position> boxes,
        std::set<Position> goals,
        Position player)
    : LevelGenerator(w, h, boxes.size(), false)
    , m_goals(goals)
    , m_initialState(player, boxes, -1)
{
    m_map.init(w, h, v);
    m_positionSelector.init(v);
}

bool LevelSolver::solve()
{
    m_closedSet.clear();
    m_parents.clear();
    m_openSet.clear();

    Map tempMap = m_map;
    Position minPos = m_initialState.getPlayer();
    for(const auto& b : m_initialState.getBoxes())
    {
        m_map(b) = BOX;
    }
    floodfill(m_initialState.getPlayer(), minPos);
    m_initialState = State(minPos, m_initialState.getBoxes(), -1);
    m_map = tempMap;

    const auto playerPositions = m_positionSelector.initPlayer(m_goals);

    for (const auto& p : playerPositions)
    {
        State state(p, m_goals, 0);
        m_openSet.push_back(state);
        m_closedSet.insert(std::pair<State, size_t>(state, 0));
    }

    while(!m_openSet.empty())
    {
        const State current = m_openSet.front();
        m_openSet.pop_front();

        if (current == m_initialState)
        {
            storeSolution(current);
            return true;
        }

        auto states = expand(current);
        for(const auto& s : states)
        {
            if (m_closedSet.count(s) == 0)
            {
                m_openSet.push_back(s);
                size_t pValue = 0;
                pValue = m_closedSet.find(current)->second;
                pValue += 1;
                m_closedSet.insert(std::pair<State, size_t>(s, pValue));
                m_parents.insert(std::pair<State, State>(s, current));
            }
        }
    }

    return false;
}

void LevelSolver::storeSolution(State initial)
{
    State t = initial;
    std::vector<State> states;
    states.push_back(t);
    while (m_parents.find(t) != m_parents.end())
    {
        states.push_back(m_parents.find(t)->second);
        t = m_parents.find(t)->second;
    }
    m_solutionHandler.update(m_map, m_goals, states);
}
