
#include "Pattern.h"
#include "MapGenerator.h"
#include "LevelGenerator.h"
#include "FileWriter.h"
#include "InputParser.h"
#include "Util.h"

#define N 3
#define M 3

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));
    string widthOption, heightOption, numBoxesOption, outFile;
    int width, height, numBoxes;

    InputParser parser(argc, argv);
    width = parser.GetOption("--width", widthOption)
            ? stoi(widthOption) : 2;
    height = parser.GetOption("--height", heightOption)
            ? stoi(heightOption) : 2;
    numBoxes = parser.GetOption("--numBoxes", numBoxesOption)
            ? stoi(numBoxesOption) : 2;
    if (!parser.GetOption("-o", outFile))
    {
        outFile = "out";
    }

    MapGenerator mgen(width, height, M, N, numBoxes);
    LevelGenerator lgen(width*M, height*N, numBoxes);

    set<Pattern> p;
    if (!mgen.loadPatterns("./patterns"))
    {
        cout << "Could not load patterns from file" << endl;
        return -1;
    }

    int attempt = 1;
    int max = 0;
    int actual;

    cout << "Generating level";

    while(true) 
    {
        while(!mgen.generate());
    
        while(true)
        {
            actual = lgen.generate(mgen.getMap());
            if(max < actual) max = actual;
            //cout << "Attempt " << attempt << ", actual result: " << actual << ", best: " << max << "\n";
            cout << "." << std::flush;
            if(attempt++ % 5 == 0) break;
        }
        if(attempt >= 100) break;
    }

    cout << "finished!\n\n";

    cout << "Size: " << width*M << "x" << height*N << "\n";
    cout << "Number of boxes: " << numBoxes << "\n";
    cout << "Difficulty (measured as the sum of\nbox lines and box changes): " << max << "\n\n";

    lgen.calculateSolution();
    lgen.placeBest();

    if (outFile.size() == 0)
    {
        outFile = "./output";
    }

    FileWriter::writeMapToFile(lgen.getMap(), width*M, height*N, outFile, lgen.getSolution());

    return 0;
}
