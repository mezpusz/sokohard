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

std::vector<Position> PositionSelector::initPlayer(std::set<Position> boxes)
{
    size_t count = 0;
    std::vector<Position> positions;
    Position p, min;

    Map tempMap = m_map;

    for(const auto& box : boxes)
    {
        m_map(box) = BOX;
    }

    while(count != available - numBoxes)
    {
        p.x = Random(0, width);
        p.y = Random(0, height);

        min = p;

        if(m_map(p) != EMPTY)
        {
            continue;
        }
        count += floodfill(p, min);
        positions.push_back(min);
    }
    m_map = tempMap;

    return positions;
}

Position PositionSelector::placePlayer(std::set<Position> boxes, Position prev)
{
    Position min;

    Map tempMap = m_map;

    for(const auto& b : boxes)
    {
        m_map(b) = BOX;
    }

    min = prev;
    floodfill(prev, min);
    m_map = tempMap;

    return min;
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
            p += direction[Random(0,4)];
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
