#pragma once

#include "Util.h"
#include "State.h"
#include "Map.h"

class LevelGenerator
{
private:

	int width; // x koord
	int height; // y koord
	int numBoxes;
	int available;

	Map m_map;
	Map m_bestMap;
	State m_best;
	int m_max;
	vector<State> m_bestSolution;
	string m_solution;
	set<Position> m_bestGoals;

	static const Position direction[];

	set<Position> goals;

	deque<State> openSet;
	set<State> checked;
	map<State, int> closedSet;
	map<State, State> parents;

private:

	vector<Position> initPlayer(set<Position> boxes);
	Position placePlayer(set<Position> boxes, Position prev);
	int floodfill(Position p, Position& min);
	void placeGoals();
	vector<State> expand(State s);

public:
	LevelGenerator(int w, int h, int n);
	int generate(vector<char> v);
	vector<char>& getMap();
	void printMap() const;
	void placeBest();
	void printBest();
	void calculateSolution();
	string getSolution() const;
	int getMax() const;
};
