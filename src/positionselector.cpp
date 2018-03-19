#include "positionselector.h"

#include "map_elements.h"
#include "util.h"

#include <iostream>

PositionSelector::PositionSelector(size_t width, size_t height, size_t boxNum)
    : width(width)
    , height(height)
    , numBoxes(boxNum)
    , available(0)
    , m_map()
{
}

void PositionSelector::init(std::vector<char> v)
{
    available = 0;

    m_map.init(width, height, v);

    for(const auto& c : m_map)
    {
        if(c == EMPTY)
        {
            available++;
        }
    }
}

std::vector<std::set<Position>> PositionSelector::initPlayer(std::set<Position> boxes)
{
    size_t count = 0;
    std::vector<std::set<Position>> positionsVector;
    std::set<Position> availables;
    Position p, min;

    Map tempMap = m_map;

    for(const auto& box : boxes)
    {
        m_map(box) = BOX;
    }
    for(const auto& box : boxes)
    {
        for(const auto d : directions)
        {
            Position pos = box + d;
            if (box.isInInterval(Position(0,0),Position(width,height),d)
                && (m_map(pos) == EMPTY))
            {
                availables.insert(pos);
            }
        }
    }

    while(count != available - numBoxes)
    {
        std::set<Position> positions;
        p.x = Random(0, width);
        p.y = Random(0, height);
        min = p;
        count += floodfill(p, min);
        for(auto it = availables.begin(); it != availables.end();)
        {
            if (m_map(*it) == '_') {
                positions.insert(*it);
                it = availables.erase(it);
            } else {
                it++;
            }
        }
        positionsVector.push_back(positions);
    }
    m_map = tempMap;

    return positionsVector;
}

std::set<Position> PositionSelector::placePlayer(std::set<Position> boxes, Position prev)
{
    std::set<Position> result;
    Position min;

    Map tempMap = m_map;

    for(const auto& b : boxes)
    {
        m_map(b) = BOX;
    }

    min = prev;
    floodfill(prev, min);
    for(const auto& b : boxes)
    {
        for(const auto& d : directions)
        {
            if (b.isInInterval(Position(0,0),Position(width, height), d)
                && m_map(b+d) == '_')
            {
                result.insert(b + d);
            }
        }
    }
    m_map = tempMap;

    return result;
}

std::set<Position> PositionSelector::placeGoals()
{
    size_t count;
    bool success = false;
    Position p;
    std::set<Position> positions;

    while (!success)
    {
        p = Position(Random(0,width),Random(0,height));

        count = 0;
        positions.clear();

        while (m_map(p) == EMPTY
            && positions.find(p) == positions.end())
        {
            count++;
            positions.insert(p);
            p += directions[Random(0,4)];
            if (!p.isInInterval(Position(0,0),Position(width,height),Position(0,0)))
            {
                break;
            }
            if (count == numBoxes)
            {
                success = true;
                break;
            }
        }
    }

    return positions;
}

size_t PositionSelector::floodfill(Position p, Position& min)
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
