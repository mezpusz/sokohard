#pragma once

#include "Util.h"

class State
{
private:
    int numBoxes;

    set<Position> boxPos;
    Position playerPos;

    set<Position>::iterator movedBox;

public:
    State(Position p, set<Position> b, Position moved);
    State(const State& rhs);
    State() {}

    State& operator=(const State& rhs);
    bool operator==(const State& rhs) const;
    bool operator<(const State& rhs) const;

    Position getPlayerPos() const;
    set<Position> getBoxPos() const;
    int getNumBoxes() const;
    Position getMoved() const;

    void setPlayerPos(Position p);
    void setBoxPos(set<Position> p);

    void printState();
};
