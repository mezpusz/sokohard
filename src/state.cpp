#include "state.h"

State::State(Position p, std::set<Position> b, Position moved)
    : numBoxes(b.size())
    , boxPos(b.begin(), b.end())
    , playerPos(p)
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
    return (playerPos < rhs.getPlayerPos()
        || (playerPos == rhs.getPlayerPos() && boxPos < rhs.getBoxPos()));
}

Position State::getPlayerPos() const
{
    return static_cast<Position>(playerPos);
}

std::set<Position> State::getBoxPos() const
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

void State::setBoxPos(std::set<Position> p)
{
    boxPos = p;
}

std::ostream& operator<<(std::ostream& os, const State& state)
{
    os << "Player: (" << state.playerPos.x
       << "," << state.playerPos.y << ")\n";

    for(const auto& b : state.boxPos)
    {
        os << "(" << b.x << "," << b.y << ")\n";
    }

    os << '\n';
    return os;
}
