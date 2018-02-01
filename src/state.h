#pragma once

#include "position.h"

#include <ostream>
#include <set>

class State
{
public:
    State(Position p, std::set<Position> b, Position moved);
    State(const State& rhs);
    State() = default;

    State& operator=(const State& rhs);
    bool operator==(const State& rhs) const;
    bool operator<(const State& rhs) const;

    Position getPlayerPos() const;
    std::set<Position> getBoxPos() const;
    int getNumBoxes() const;
    Position getMoved() const;

    void setPlayerPos(Position p);
    void setBoxPos(std::set<Position> p);

    friend std::ostream& operator<<(std::ostream& os, const State& state);

private:
    int numBoxes;

    std::set<Position> boxPos;
    Position playerPos;

    std::set<Position>::iterator movedBox;
};

std::ostream& operator<<(std::ostream& os, const State& state);
