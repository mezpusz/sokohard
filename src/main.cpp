
#include "pattern.h"
#include "mapgenerator.h"
#include "levelgenerator.h"
#include "filewriter.h"
#include "inputparser.h"
#include "util.h"

#include <iostream>
#include <set>
#include <string>

#define N 3
#define M 3

int main(int argc, char* argv[])
{
    std::string widthOption, heightOption, numBoxesOption,
        seedOption,
        outFile;
    size_t width, height, numBoxes;
    unsigned seed;
    bool box_changes;

    InputParser parser(argc, argv);
    width = parser.GetOption("-w", widthOption)
            ? stoi(widthOption) : 2;
    height = parser.GetOption("-h", heightOption)
            ? stoi(heightOption) : 2;
    numBoxes = parser.GetOption("-b", numBoxesOption)
            ? stoi(numBoxesOption) : 2;
    seed = parser.GetOption("-s", seedOption)
            ? stoi(seedOption) : time(nullptr);
    box_changes = parser.GetBoolOption("--box-changes");
    if (!parser.GetOption("-o", outFile))
    {
        outFile = "out";
    }

    std::cout << "Size: " << width*M << "x" << height*N << ", boxes: "
        << numBoxes << ", seed: " << seed << std::endl;
    seedRandom(seed);
    MapGenerator mgen(width, height, M, N, numBoxes);
    LevelGenerator lgen(width*M, height*N, numBoxes, box_changes);

    size_t attempt = 1;

    std::cout << "Generating level";

    while(true) 
    {
        while(!mgen.generate());
    
        while(true)
        {
            lgen.generate(mgen.getMap());
            std::cout << "." << std::flush;
            if(attempt++ % 5 == 0) break;
        }
        if(attempt >= 100) break;
    }

    std::cout << "finished!" << std::endl;

    std::cout << "Difficulty: " << lgen.getMax() << std::endl;

    lgen.calculateSolution();

    if (outFile.size() == 0)
    {
        outFile = "./output";
    }

    if(!FileWriter::writeMapToFile(lgen.placeBest(), outFile)
       || !FileWriter::writeSolutionToFile(lgen.getSolution(), outFile))
    {
        return -1;
    }

    return 0;
}
