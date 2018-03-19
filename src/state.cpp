#include "state.h"

State::State(std::set<Position> player, std::set<Position> boxes, size_t boxChange)
    : boxes(boxes.begin(), boxes.end())
    , player(player)
    , boxChange(boxChange)
{
}

State::State(const State& rhs)
    : boxes(rhs.boxes)
    , player(rhs.player)
    , boxChange(rhs.boxChange)
{
}

State& State::operator=(const State& rhs)
{
    player = rhs.player;
    boxes = rhs.boxes;
    boxChange = rhs.boxChange;
    return (*this);
}

bool State::operator==(const State& rhs) const
{
    return player == rhs.player 
        && boxes == rhs.boxes;
}

bool State::operator<(const State& rhs) const
{
    return player < rhs.player
        || (player == rhs.player
            && boxes < rhs.boxes);
}

std::set<Position> State::getPlayer() const
{
    return player;
}

std::set<Position> State::getBoxes() const
{
    return boxes;
}

size_t State::getBoxChange() const
{
    return boxChange;
}

std::ostream& operator<<(std::ostream& os, const State& state)
{
    /*os << "Player: (" << state.player.x
       << "," << state.player.y << ")\n";*/

    for(const auto& b : state.boxes)
    {
        os << "(" << b.x << "," << b.y << ")\n";
    }

    os << '\n';
    return os;
}
