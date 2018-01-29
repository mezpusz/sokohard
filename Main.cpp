
#include "Pattern.h"
#include "MapGenerator.h"
#include "LevelGenerator.h"
#include "FileWriter.h"
#include "Util.h"

#define N 3
#define M 3

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));
    int width;
    int height;
    int numBoxes;
    string fileName;
    string fn;

    if(argc == 4)
    {
        width = stoi(argv[1]);
        height = stoi(argv[2]);
        numBoxes = stoi(argv[3]);
        fileName.clear();
    } 
    else if(argc == 5)
    {
        width = stoi(argv[1]);
        height = stoi(argv[2]);
        numBoxes = stoi(argv[3]);
        fn = argv[4];
        fileName.assign(fn.begin(), fn.end());
    }
    else
    {
        cout << "Parameters must be: <sizeX> <sizeY> <boxNumber> [<filename>]\n";
        return -1;
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

    if (fileName.size() == 0)
    {
        fileName = "../Data/default";
    }

    FileWriter::writeMapToFile(lgen.getMap(), width*M, height*N, fileName, lgen.getSolution());

    return 0;
}
