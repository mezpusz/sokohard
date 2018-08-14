
#include "filereader.h"
#include "filewriter.h"
#include "inputparser.h"
#include "levelsolver.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string inputFilename;

    InputParser parser(argc, argv);
    if (!parser.GetOption("-i", inputFilename))
    {
        std::cerr << "Error: no input file" << std::endl;
        return -1;
    }

    size_t width, height;
    std::vector<char> map;
    Position player;
    std::set<Position> goals, boxes;
    if (!FileReader::parseMap(inputFilename,
                         width, height,
                         map,
                         player,
                         goals,
                              boxes)) {
        std::cerr << "Parse error" << std::endl;
        return -1;
    }

    LevelSolver solver(width, height, map, boxes, goals, player);
    if (!solver.solve())
    {
        std::cout << "Map has no solution!" << std::endl;
        return 0;
    }

    std::cout << "Solution has found, writing to " << "test" << std::endl;
    solver.calculateSolution();

    if(!FileWriter::writeSolutionToFile(solver.getSolution(), "test"))
    {
        return -1;
    }

    return 0;
}
