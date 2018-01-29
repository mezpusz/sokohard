#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "Util.h"

class FileWriter
{
public:
	static void writeMapToFile(vector<char> map, int width, int height, const string& filename, string solution);
	static vector<char> finalizeMap(vector<char> map, int width, int height);
};

#endif
