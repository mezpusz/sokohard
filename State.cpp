#include "State.h"

State::State(Position p, set<Position> b, Position moved)
	: numBoxes(b.size()), boxPos(b.begin(), b.end()), playerPos(p)
{
	movedBox = boxPos.find(moved);
}

State::State(const State& rhs)
{
	numBoxes = rhs.getNumBoxes();
	playerPos = rhs.getPlayerPos();
	boxPos = rhs.getBoxPos();
	movedBox = boxPos.find(rhs.getMoved());
}

State& State::operator=(const State& rhs)
{
	numBoxes = rhs.getNumBoxes();
	playerPos = rhs.getPlayerPos();
	boxPos = rhs.getBoxPos();
	movedBox = boxPos.find(rhs.getMoved());
	return (*this);
}

bool State::operator==(const State& rhs) const
{
	return (playerPos == rhs.getPlayerPos() && boxPos == rhs.getBoxPos());
}

bool State::operator<(const State& rhs) const
{
	return (playerPos < rhs.getPlayerPos() || 
		(playerPos == rhs.getPlayerPos() && boxPos < rhs.getBoxPos()));
}

Position State::getPlayerPos() const
{
	return static_cast<Position>(playerPos);
}

set<Position> State::getBoxPos() const
{
	return boxPos;
}

int State::getNumBoxes() const
{
	return numBoxes;
}

Position State::getMoved() const
{
	return *movedBox;
}

void State::setPlayerPos(Position p)
{
	playerPos = p;
}

void State::setBoxPos(set<Position> p)
{
	boxPos = p;
}

void State::printState()
{
	cout << "Player: (" << playerPos.x << "," << playerPos.y << ")\n";

	for(set<Position>::iterator it = boxPos.begin(); it != boxPos.end(); ++it)
	{
		cout << "(" << it->x << "," << it->y << ")\n";
	}

	cout << '\n';
}