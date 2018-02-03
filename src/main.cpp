
#include "pattern.h"
#include "mapgenerator.h"
#include "levelgenerator.h"
#include "filewriter.h"
#include "inputparser.h"

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
    int width, height, numBoxes;
    unsigned seed;

    InputParser parser(argc, argv);
    width = parser.GetOption("--width", widthOption)
            ? stoi(widthOption) : 2;
    height = parser.GetOption("--height", heightOption)
            ? stoi(heightOption) : 2;
    numBoxes = parser.GetOption("--numBoxes", numBoxesOption)
            ? stoi(numBoxesOption) : 2;
    seed = parser.GetOption("--seed", seedOption)
            ? stoi(seedOption) : time(nullptr);
    if (!parser.GetOption("-o", outFile))
    {
        outFile = "out";
    }

    std::cout << "Random seed is " << seed << std::endl;
    srand(seed);
    MapGenerator mgen(width, height, M, N, numBoxes);
    LevelGenerator lgen(width*M, height*N, numBoxes);

    std::set<Pattern> p;
    if (!mgen.loadPatterns("./patterns"))
    {
        std::cout << "Could not load patterns from file" << std::endl;
        return -1;
    }

    int attempt = 1;
    int max = 0;
    int actual;

    std::cout << "Generating level";

    while(true) 
    {
        while(!mgen.generate());
    
        while(true)
        {
            actual = lgen.generate(mgen.getMap());
            if(max < actual) max = actual;
            //cout << "Attempt " << attempt << ", actual result: " << actual << ", best: " << max << "\n";
            std::cout << "." << std::flush;
            if(attempt++ % 5 == 0) break;
        }
        if(attempt >= 100) break;
    }

    std::cout << "finished!\n\n";

    std::cout << "Size: " << width*M << "x" << height*N << "\n";
    std::cout << "Number of boxes: " << numBoxes << "\n";
    std::cout << "Difficulty (measured as the sum of\nbox lines and box changes): " << max << "\n\n";

    lgen.calculateSolution();
    lgen.placeBest();

    if (outFile.size() == 0)
    {
        outFile = "./output";
    }

    if(!FileWriter::writeMapToFile(lgen.getMap(), width*M, height*N, outFile, lgen.getSolution()))
    {
        return -1;
    }

    return 0;
}
