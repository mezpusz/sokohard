#include "levelgenerator.h"

#include "map_elements.h"
#include "util.h"

#include <iostream>

LevelGenerator::LevelGenerator(size_t w, size_t h, size_t n, bool box_changes)
    : width(w)
    , height(h)
    , numBoxes(n)
    , box_changes(box_changes)
    , positionSelector(w, h, n)
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

    goals = positionSelector.placeGoals();

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
        m_best = best;
        m_bestMap = m_map;

        m_bestSolution.clear();
        m_bestGoals.clear();
        m_bestGoals = goals;
        State t = best;
        m_bestSolution.push_back(best);
        while(parents.find(t) != parents.end())
        {
            m_bestSolution.push_back(parents.find(t)->second);
            t = parents.find(t)->second;
        }
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
    m_solution.clear();
    Position player = m_bestSolution[0].getPlayer();
    std::set<Position> boxes;
    std::set<Position> next;
    std::set<Position>::iterator b;
    std::set<Position>::iterator n;
    char pushes[] = "RLDU";
    char moves[] = "rldu";

    for (size_t i = 0; i < m_bestSolution.size()-1; ++i)
    {
        Map temp = m_bestMap;

        boxes = m_bestSolution[i].getBoxes();
        next = m_bestSolution[i+1].getBoxes();

        for (const auto& box : boxes)
        {
            m_bestMap(box) = BOX;
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
                    if (p.first.isInInterval(Position(0,0),Position(width,height),direction[i])
                        && m_bestMap(p.first + direction[i]) == EMPTY)
                    {
                        m_bestMap(p.first + direction[i]) = '_';
                        d.push_back(make_pair(p.first + direction[i],p.second + moves[i]));
                    }
                }
            }
            m_solution += str;
            player = pNext;
        }

        for(size_t i = 0; i < 4; ++i)
        {
            if(norm == direction[i])
            {
                for(size_t j = 0; j < diff.abs(); ++j)
                {
                    m_solution += pushes[i];
                }
                player += diff;
                break;
            }
        }

        m_bestMap = temp;
    }
}

void LevelGenerator::placeBest()
{
    Position player = m_best.getPlayer();

    std::set<Position> boxes = m_best.getBoxes();

    for(const auto& goal : m_bestGoals)
    {
        m_bestMap(goal) = GOAL;
    }

    for(const auto& box : boxes)
    {
        m_bestMap(box) = (m_bestGoals.find(box) == m_bestGoals.end()) ? BOX : BOX_ON_GOAL;
    }

    m_bestMap(player) = (m_bestGoals.find(player) == m_bestGoals.end()) ? PLAYER : PLAYER_ON_GOAL;

    m_map = m_bestMap;
}

void LevelGenerator::printBest()
{
    for(int i = m_bestSolution.size()-1; i >= 0; --i)
    {
        Map temp = m_bestMap;

        Position player = m_bestSolution[i].getPlayer();
        std::set<Position> boxes = m_bestSolution[i].getBoxes();

        for(const auto& goal : m_bestGoals)
        {
            m_bestMap(goal) = GOAL;
        }

        for(const auto& box : boxes)
        {
            m_bestMap(box) = (m_bestGoals.find(box) == m_bestGoals.end()) ? BOX : BOX_ON_GOAL;
        }

        m_bestMap(player) = (m_bestGoals.find(player) == m_bestGoals.end()) ? PLAYER : PLAYER_ON_GOAL;

        std::cout << m_bestMap;
        m_bestMap = temp;
    }
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

const Position LevelGenerator::direction[] = { Position(1,0), Position(-1,0), Position(0,1), Position(0,-1) };
