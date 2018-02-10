#pragma once

#include <algorithm>

struct Position
{
    int x;
    int y;

    Position()
        : x(0)
        , y(0)
    {
    }

    Position(int a, int b)
        : x(a)
        , y(b)
    {
    }

    Position& operator+=(const Position& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return (*this);
    }

    Position operator+(const Position& rhs) const
    {
        return Position(x + rhs.x, y + rhs.y);
    }
    
    bool operator<(const Position& rhs) const
    {
        return ((x < rhs.x) || (x == rhs.x && y < rhs.y));
    }

    bool operator==(const Position& rhs) const
    {
        return (x == rhs.x && y == rhs.y);
    }

    Position diff(const Position rhs) const
    {
        return Position(rhs.x - x, rhs.y - y);
    }

    Position inv() const
    {
        return Position(-x, -y);
    }

    Position normal() const
    {
        return Position((x != 0) ? x/std::abs(x) : 0, (y != 0) ? y/std::abs(y) : 0);
    }

    int abs() const
    {
        return (x != 0) ? std::abs(x) : std::abs(y);
    }

    bool isInInterval(Position min, Position max, Position offset) const
    {
        Position p(x + offset.x, y + offset.y); 

        return (p.x >= min.x && p.y >= min.y
                && p.x < max.x && p.y < max.y);
    }
};
