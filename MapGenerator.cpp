#include "MapGenerator.h"


MapGenerator::MapGenerator(int w, int h, int m, int n, int num)
	: width(w), height(h), n(n), m(m), numBoxes(num)
{
	patterns.clear();
}

bool MapGenerator::generate()
{
	bool match;

	int numPatterns = patterns.size();
	int ptry;

	charMap.init(width*m, height*n, '0');
	patternMap.resize(width*height);

	do {

		for(int j = 0; j < height; ++j)
		{
			for(int i = 0; i < width; ++i)
			{
				Pattern p;
				ptry = 0;

				do {
					set<Pattern>::iterator it = patterns.begin();
					advance(it, Random(0, numPatterns-1));
					p = *it;
					match = true;

					if(i > 0 && j > 0 && !p.match(patternMap[(j-1)*width + i - 1], NORTH_WEST))
					{
						match = false;
					}
					if(j > 0 && !p.match(patternMap[(j-1)*width + i], NORTH))
					{
						match = false;
					}
					if(i < (width - 1) && j > 0 && !p.match(patternMap[(j-1)*width + i + 1], NORTH_EAST))
					{
						match = false;
					}
					if(i > 0 && !p.match(patternMap[j*width + i - 1], WEST))
					{
						match = false;
					}

					ptry++;
					if(ptry > 100)
					{
						return false;
					}

				} while(!match);

				patternMap[j*width + i] = p;
				setCharMap(p, i, j);
			}
		}

	} while(!isConnected() || checkForOpenSections() || checkForDeadEnds());

	//printMap();

	return true;
}

vector<char>& MapGenerator::getMap()
{
	return charMap.getMap();
}

void MapGenerator::setCharMap(Pattern& p, int i, int j)
{
	vector<char> v = p.getPatternAsVector();
	for(int k = 0; k < m; ++k)
	{
		for(int l = 0; l < n; ++l)
		{
			charMap(m*i + k, n*j + l) = v[(l+1)*(m+2) + k + 1];
		}
	}
}

bool MapGenerator::isConnected()
{
	int rCount = 0;
	bCount = 0;

	Map tempMap = charMap;

	for(int i = 0; i < width*m; ++i)
	{
		for(int j = 0; j < height*n; ++j)
		{
			if(charMap(i,j) == ' ') rCount++;
		}
	}

	// Ha nincs eleg hely az osszes doboznak, a jatekosnak
	// es legalabb egy ures helynek, restart
	if(rCount < numBoxes + 2) return false;

	for(int i = 0; i < width*m; ++i)
	{
		for(int j = 0; j < height*n; ++j)
		{
			if(charMap(i,j) == ' ')
			{
				dfs(i,j);
				break;
			}
		}
		if(bCount > 0) break;
	}

	charMap = tempMap;

	//cout << rCount << " " << bCount << endl;

	return (rCount == bCount) && (rCount > 0);
}

void MapGenerator::dfs(int i, int j)
{
	//cout << i << " + " << j << endl;

	if((charMap(i,j) == ' '))
	{
		charMap(i,j) = '_';
		bCount++;

		if(i > 0)			dfs(i-1, j);
		if(i < width*m)		dfs(i+1, j);
		if(j > 0)			dfs(i, j-1);
		if(j < height*n)	dfs(i, j+1);
	}
}

bool MapGenerator::checkForOpenSections()
{
	int x = 0, y = 0;

	for(int i = 0; i < width*m; ++i)
	{
		for(int j = 0; j < height*n; ++j)
		{
			if(charMap(i,j) == ' ' && i + 4 <= width*m && j + 3 <= height*n)
			{
				for(int k = i; k < i + 4; ++k)
				{
					for(int l = j; l < j + 3; ++l)
					{
						if(charMap(k,l) == ' ') y++;
						else break;
					}
					if(y >= 3) x++;
					y = 0;
				}
				if(x >= 4) return true;
				x = 0;
			}
			if(charMap(i,j) == ' ' && i + 3 <= width*m && j + 4 <= height*n)
			{
				for(int k = i; k < i + 3; ++k)
				{
					for(int l = j; l < j + 4; ++l)
					{
						if(charMap(k,l) == ' ') y++;
						else break;
					}

					if(y >= 4) x++;
					y = 0;
				}
				if(x >= 3) return true;
				x = 0;
			}
		}
	}
	return false;
}

bool MapGenerator::checkForDeadEnds()
{
	for(int i = 0; i < width*m; ++i)
	{
		for(int j = 0; j < height*n; ++j)
		{
			if(((j-1 >= 0 && charMap(i,j-1) == '#') || j-1 < 0) && ((j+1 < height*n && charMap(i,j+1) == '#') || j+1 >= height*n))
			{
					if((i-1 >= 0 && charMap(i-1,j) == '#') || i-1 < 0) return true;
					if((i+1 < width*m && charMap(i+1,j) == '#') || i+1 >= width*m) return true;
			}

			if(((i-1 >= 0 && charMap(i-1,j) == '#') || i-1 < 0) && ((i+1 < width*m && charMap(i+1,j) == '#') || i+1 >= width*m))
			{
					if((j-1 >= 0 && charMap(i,j-1) == '#') || j-1 < 0) return true;
					if((j+1 < height*n && charMap(i,j+1) == '#') || j+1 >= height*n) return true;
			}
		}
	}
	return false;
}

void MapGenerator::printMap() const
{
	charMap.printMap();
}

void MapGenerator::loadPatterns(const string& filename)
{
	ifstream fin(filename, ios::binary);
	string line;
	string pattern = "";

    if (fin.is_open())
    {
        while (getline(fin, line))
		{
			if(line.size() == 1)
			{
				Pattern pat, p1;
				pat.Initialize(n,m,pattern);

				for(int r = R0; r != R270; ++r)
				{
					pat.getPattern(p1, static_cast<ROTATION>(r), false);
					patterns.insert(p1);

					pat.getPattern(p1, static_cast<ROTATION>(r), true);
					patterns.insert(p1);
				}

				pattern = "";
			}
			else
			{
				pattern += line.substr(0,5);
			}
		}
		fin.close();
	} 
	else 
	{
		cout << "Missing pattern.txt file!\n";
		cin.get();
	}
}
