#pragma once

#include <vector>
#include <set>
#include <deque>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

typedef enum ROTATION	// Az elforgatas merteke
{
	R0,					// 0 fok
	R90,				// 90 fok
	R180,				// 180 fok
	R270				// 270 fok
};

typedef enum JOIN		// Illeszkedes a mintak kozt,
{						// clockwise koruljarasban

	NORTH = 0x1,				// felso sor
	EAST = 0x2,					// jobb oldali oszlop
	SOUTH = 0x4,				// also sor
	WEST = 0x8,					// bal oldali oszlop
	NORTH_EAST = NORTH | EAST,	// jobb felso
	SOUTH_EAST = SOUTH | EAST,	// jobb also
	SOUTH_WEST = SOUTH | WEST,	// bal also
	NORTH_WEST = NORTH | WEST	// bal felso sarok
};

struct Position
{
	int x;
	int y;

	Position() : x(0), y(0) {}
	Position(int a, int b) : x(a), y(b) {}

	Position& operator=(const Position& rhs)
	{
		x = rhs.x;
		y = rhs.y;

		return (*this);
	}

	Position& operator+=(const Position& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return (*this);
	}

	Position operator+(const Position& rhs)
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

inline int Random(int first, int last)
{
	return rand() % (last-first) + first;
}
