#pragma once

#include "position.h"

#include <ostream>
#include <set>

class State
{
public:
    State(std::set<Position> player, std::set<Position> boxes, size_t boxChange);
    State(const State& rhs);
    State() = default;

    State& operator=(const State& rhs);
    bool operator==(const State& rhs) const;
    bool operator<(const State& rhs) const;

    std::set<Position> getPlayer() const;
    std::set<Position> getBoxes() const;
    size_t getBoxChange() const;

    friend std::ostream& operator<<(std::ostream& os, const State& state);

private:
    std::set<Position> boxes;
    std::set<Position> player;
    size_t boxChange;
};

std::ostream& operator<<(std::ostream& os, const State& state);
