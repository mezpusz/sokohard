#include "filereader.h"

#include "map_elements.h"
#include "position.h"

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

bool FileReader::parseMap(const std::string& filename,
                          size_t& width, size_t& height,
                          std::vector<char>& map,
                          Position& player,
                          std::set<Position>& goals,
                          std::set<Position>& boxes)
{
    std::ifstream mapFile(filename);

    if(!mapFile.is_open())
    {
        return false;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(mapFile, line))
    {
        lines.push_back(line);
    }
    
    width = 0;
    height = lines.size();
    for (const auto& s : lines) {
        if (width < s.size()) {
            width = s.size();
        }
    }
    player = INVALID;
    boxes.clear();
    goals.clear();
    map.clear();
    
    Position current(0, 0);
    for (auto& line : lines) {
        auto it = line.begin();
        while (it != line.end() && *it != WALL) {
            *it = WALL;
            it++;
            current.x++;
        }
        auto lastWall = it;
        auto lastWallPos = current;
        while (it != line.end()) {
            switch (*it) {
                case EMPTY: {
                    break;
                }
                case WALL: {
                    lastWall = it;
                    lastWallPos = current;
                    break;
                }
                case GOAL: {
                    goals.insert(current);
                    *it = EMPTY;
                    break;
                }
                case PLAYER: {
                    if (player == INVALID) {
                        player = current;
                        *it = EMPTY;
                        break;
                    }
                    std::cerr << "Error: Multiple players found on map" << std::endl;
                    return false;
                }
                case PLAYER_ON_GOAL: {
                    if (player == INVALID) {
                        player = current;
                    } else {
                        std::cerr << "Error: Multiple players found on map" << std::endl;
                        return false;
                    }
                    goals.insert(current);
                    *it = EMPTY;
                    break;
                }
                case BOX: {
                    boxes.insert(current);
                    *it = EMPTY;
                    break;
                }
                case BOX_ON_GOAL: {
                    goals.insert(current);
                    boxes.insert(current);
                    *it = EMPTY;
                    break;
                }
                default: {
                    std::cerr << "Error: Invalid character " << *it << " at position "
                              << current.x << "," << current.y << std::endl;
                    *it = EMPTY;
                    break;
                }
            }
            it++;
            current.x++;
        }
        while (lastWall != line.end()) {
            if (player == lastWallPos) {
                std::cerr << "Error: Player is outside the walls" << std::endl;
                return false;
            }
            boxes.erase(lastWallPos);
            goals.erase(lastWallPos);
            *lastWall = WALL;
            lastWall++;
        }
        for (size_t w = line.size(); w < width; ++w) {
            line.push_back(WALL);
        }
        for (const auto& c : line) {
            map.push_back(c);
        }
        current.y++;
        current.x = 0;
    }

    return true;
}
