#ifndef MAP_H
#define MAP_H

#include "Util.h"

class Map
{
private:

	int m_width;
	int m_height;

	vector<char> m_map;

public:

	Map();
	Map(const Map& rhs);

	void init(int width, int height, char c);
	void init(int width, int height, vector<char> in);

	char& operator()(int x, int y) const;
	char& operator()(int x, int y);
	char& operator()(Position p) const;
	char& operator()(Position p);
	Map& operator=(Map& rhs);
	vector<char>& getMap();
	vector<char>::iterator begin();
	vector<char>::iterator end();
	vector<char>::const_iterator cbegin() const;
	vector<char>::const_iterator cend() const;
	int width() const;
	int height() const;

	void printMap() const;
};

#endif // MAP_H

