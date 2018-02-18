#include "solutionhandler.h"

#include "map_elements.h"
#include "util.h"

#include <deque>
#include <iostream>

SolutionHandler::SolutionHandler()
    : m_map()
    , m_goals()
    , m_states()
{
}

void SolutionHandler::init(Map map, std::set<Position> goals, std::vector<State> states)
{
    m_map = map;
    m_goals = goals;
    m_states = states;
}

std::string SolutionHandler::calculateSolution()
{
    std::string solution;
    Position player = m_states[0].getPlayer();
    std::set<Position> boxes;
    std::set<Position> next;
    std::set<Position>::iterator b;
    std::set<Position>::iterator n;
    char pushes[] = "RLDU";
    char moves[] = "rldu";

    for (size_t i = 0; i < m_states.size()-1; ++i)
    {
        Map temp = m_map;

        boxes = m_states[i].getBoxes();
        next = m_states[i+1].getBoxes();

        for (const auto& box : boxes)
        {
            m_map(box) = BOX;
        }

        b = boxes.begin();
        n = next.begin();

        while (boxes.find(*n) != boxes.end())
        {
            n++;
        }
        while (next.find(*b) != next.end())
        {
            b++;
        }

        Position diff = (*b).diff(*n);
        Position norm = diff.normal();
        Position pNext = *b;
        pNext += norm.inv();

        if (!(pNext == player))
        {
            std::string str;
            std::deque<std::pair<Position, std::string>> d;

            d.push_back(make_pair(player, std::string()));

            while (!d.empty())
            {
                std::pair<Position, std::string> p = d.front();
                d.pop_front();

                if (p.first == pNext)
                {
                    str = p.second;
                    break;
                }

                for (size_t i = 0; i < 4; ++i)
                {
                    if (p.first.isInInterval(Position(0,0),Position(m_map.width(),m_map.height()),direction[i])
                        && m_map(p.first + direction[i]) == EMPTY)
                    {
                        m_map(p.first + direction[i]) = '_';
                        d.push_back(make_pair(p.first + direction[i],p.second + moves[i]));
                    }
                }
            }
            solution += str;
            player = pNext;
        }

        for(size_t i = 0; i < 4; ++i)
        {
            if(norm == direction[i])
            {
                for(size_t j = 0; j < diff.abs(); ++j)
                {
                    solution += pushes[i];
                }
                player += diff;
                break;
            }
        }
        m_map = temp;
    }
    return solution;
}

Map SolutionHandler::placeBest()
{
    Position player = m_states[0].getPlayer();

    std::set<Position> boxes = m_states[0].getBoxes();

    for(const auto& goal : m_goals)
    {
        m_map(goal) = GOAL;
    }

    for(const auto& box : boxes)
    {
        m_map(box) = (m_goals.find(box) == m_goals.end()) ? BOX : BOX_ON_GOAL;
    }

    m_map(player) = (m_goals.find(player) == m_goals.end()) ? PLAYER : PLAYER_ON_GOAL;
    return m_map;
}

void SolutionHandler::printBest()
{
    for(int i = m_states.size()-1; i >= 0; --i)
    {
        Map temp = m_map;

        Position player = m_states[i].getPlayer();
        std::set<Position> boxes = m_states[i].getBoxes();

        for(const auto& goal : m_goals)
        {
            m_map(goal) = GOAL;
        }

        for(const auto& box : boxes)
        {
            m_map(box) = (m_goals.find(box) == m_goals.end()) ? BOX : BOX_ON_GOAL;
        }

        m_map(player) = (m_goals.find(player) == m_goals.end()) ? PLAYER : PLAYER_ON_GOAL;

        std::cout << m_map;
        m_map = temp;
    }
}
