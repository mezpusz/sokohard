#include "levelgenerator.h"

#include "util.h"

LevelGenerator::LevelGenerator(int w, int h, int n)
	: width(w)
	, height(h)
	, numBoxes(n)
	, available(0)
	, m_max(0)
{
}

int LevelGenerator::generate(std::vector<char> v)
{
	available = 0;

	m_map.init(width,height,v);

	for(std::vector<char>::iterator it = m_map.begin(); it != m_map.end(); ++it)
	{
		if(*it == ' ')
		{
			available++;
		}
	}

	closedSet.clear();
	parents.clear();
	openSet.clear();
	checked.clear();

	placeGoals();

	std::set<Position> ps;

	ps.insert(goals.begin(), goals.end());

	std::vector<Position> pPos = initPlayer(ps);

	for(unsigned int i = 0; i < pPos.size(); ++i)
	{
		openSet.push_back(State(pPos[i], ps, Position(-1,-1)));
		checked.insert(State(pPos[i], ps, Position(-1,-1)));
	}

	while(true)
	{
		if(openSet.empty()) break;
		State s = openSet.front();
		openSet.pop_front();

		std::vector<State> states = expand(s);
		
		std::map<State, State>::iterator it = parents.find(s);
		if (it == parents.end())
		{
			closedSet.insert(std::pair<State, int>(s, 0));
		}
		else
		{
			State child = it->first;
			State parent = it->second;
			int pValue = closedSet.find(parent)->second;
			bool boxChange = (child.getBoxPos().count(parent.getMoved()) != 0);
			if(boxChange) pValue+=1;
			closedSet.insert(std::pair<State, int>(s, pValue+1));
		}


		for(unsigned int i = 0; i < states.size(); ++i)
		{
			if (checked.count(states[i]) == 0)
			{
				openSet.push_back(states[i]);
				checked.insert(states[i]);
				parents.insert(std::pair<State, State>(states[i], s));
			}
		}
	}

	int max = 0;
	State best;

	for(std::map<State, int>::iterator it = closedSet.begin(); it != closedSet.end(); ++it)
	{
		if(it->second >= max)
		{
			max = it->second;
			best = it->first;
		}
	}

	if(m_max < max)
	{
		m_max = max;
		m_best = best;
		m_bestMap = m_map;

		m_bestSolution.clear();
		m_bestGoals.clear();
		m_bestGoals = goals;
		State t = best;
		m_bestSolution.push_back(best);
		while(parents.find(t) != parents.end())
		{
			m_bestSolution.push_back(parents.find(t)->second);
			t = parents.find(t)->second;
		}
	}

	return max;
}

std::vector<Position> LevelGenerator::initPlayer(std::set<Position> boxes)
{
	int count = 0;
	std::vector<Position> pos;
	Position p, min;

	Map tempMap = m_map;

	for(std::set<Position>::iterator it = boxes.begin(); it != boxes.end(); ++it)
	{
		m_map(*it) = '$';
	}

	while(count != available - numBoxes)
	{
		p.x = Random(0, width);
		p.y = Random(0, height);

		min = p;

		if(m_map(p) != ' ') 
		{
			continue;
		}
		count += floodfill(p, min);
		pos.push_back(min);
	}
	m_map = tempMap;

	return pos;
}

Position LevelGenerator::placePlayer(std::set<Position> boxes, Position prev)
{
	int count = 0;
	Position min;

	Map tempMap = m_map;

	for(std::set<Position>::iterator it = boxes.begin(); it != boxes.end(); ++it)
	{
		m_map(*it) = '$';
	}

	min = prev;
	count += floodfill(prev, min);
	m_map = tempMap;

	return min;
}

int LevelGenerator::floodfill(Position p, Position& min)
{
	if (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height) return 0;
	if (m_map(p) != ' ') return 0;
	
	int c = 1;
	if(p < min) min = p;

	m_map(p) = '_';

	c += floodfill(Position(p.x + 1, p.y), min);
	c += floodfill(Position(p.x - 1, p.y), min);
	c += floodfill(Position(p.x, p.y + 1), min);
	c += floodfill(Position(p.x, p.y - 1), min);

	return c;
}

std::vector<char>& LevelGenerator::getMap()
{
	return m_map.getMap();
}

std::vector<State> LevelGenerator::expand(State s)
{
	std::vector<State> eStates;
	Position min(0,0);
	Position max(width, height);

	Map tempMap = m_map;

	Position minPos = s.getPlayerPos();
	std::set<Position> boxes = s.getBoxPos();
	for(std::set<Position>::iterator it = boxes.begin(); it != boxes.end(); ++it)
	{
		m_map(*it) = '$';
	}
	floodfill(s.getPlayerPos(), minPos);

	Map floodedMap = m_map;
	m_map = tempMap;

	for(std::set<Position>::iterator it = boxes.begin(); it != boxes.end(); ++it)
	{
		Position actual;

		for(int i = 0; i < 4; ++i)
		{
			if((*it).isInInterval(min,max,direction[i]) && floodedMap(it->x + direction[i].x,it->y + direction[i].y) == '_')
			{
				actual = *it;
				actual += direction[i];

				while(actual.isInInterval(min,max,direction[i]) && floodedMap(actual + direction[i]) == '_')
				{
					std::set<Position> ps(boxes.begin(), boxes.end());
					Position pushedBox = *(ps.find(*it));
					ps.erase(pushedBox);
					pushedBox = actual;
					ps.insert(pushedBox);
					Position newPlayer = placePlayer(ps, actual + direction[i]);
					eStates.push_back(State(newPlayer, ps, pushedBox));
					actual += direction[i];
				}
			}
		}
	}
	return eStates;
}

void LevelGenerator::calculateSolution()
{
	m_solution.clear();
	Position player = m_bestSolution[0].getPlayerPos();
	std::set<Position> boxes;
	std::set<Position> next;
	std::set<Position>::iterator b;
	std::set<Position>::iterator n;
	char s[] = "RLDU";
	char s1[] = "rldu";

	for(unsigned int i = 0; i < m_bestSolution.size()-1; ++i)
	{
		Map temp = m_bestMap;

		boxes = m_bestSolution[i].getBoxPos();
		next = m_bestSolution[i+1].getBoxPos();

		for(std::set<Position>::iterator it = boxes.begin(); it != boxes.end(); ++it)
		{
			m_bestMap(*it) = '$';
		}

		b = boxes.find(m_bestSolution[i].getMoved());
		n = next.begin();

		while (true)
		{
			if (boxes.find(*n) == boxes.end()) break;
			n++;
		}

		Position diff = (*b).diff(*n);
		Position norm = diff.normal();
		Position pNext = *b;
		pNext += norm.inv();

		if(!(pNext == player))
		{
			string str;
			std::deque<pair<Position, string>> d;

			d.push_back(make_pair(player, string()));

			while(!d.empty())
			{
				std::pair<Position, std::string> p = d.front();
				d.pop_front();

				if(p.first == pNext) 
				{
					str = p.second;
					break;
				}

				for(int i = 0; i < 4; ++i)
				{
					if(p.first.isInInterval(Position(0,0),Position(width,height),direction[i])
						&& m_bestMap(p.first + direction[i]) == ' ')
					{
						m_bestMap(p.first + direction[i]) = '_';
						d.push_back(make_pair(p.first + direction[i],p.second + s1[i]));
					}
				}
			}
			m_solution += str;
			player = pNext;
		}

		for(int i = 0; i < 4; ++i)
		{
			if(norm == direction[i])
			{
				for(int j = 0; j < diff.abs(); ++j) m_solution += s[i];
				player += diff;
				break;
			}
		}

		m_bestMap = temp;
	}
}

void LevelGenerator::placeGoals()
{
	//cout << "Placing goals...";
	int count;
	bool success = false;
	Position p;
	std::set<Position> pos;

	goals.clear();

	while(!success)
	{
		p = Position(Random(0,width),Random(0,height));

		count = 0;
		pos.clear();

		while(m_map(p) == ' ' && pos.find(p) == pos.end())
		{
			//cout << p.x << " " << p.y << endl;
			count++;
			pos.insert(p);
			p += direction[Random(0,4)];
			if(!p.isInInterval(Position(0,0),Position(width,height),Position(0,0))) break;
			if(count == numBoxes)
			{
				success = true;
				break;
			}
		}
	}

	goals = pos;

	//cout << "finished!\n";
}

void LevelGenerator::placeBest()
{
	//cout << "Placing boxes and player...";

	Position player = m_best.getPlayerPos();

	std::set<Position> boxes = m_best.getBoxPos();

	for(std::set<Position>::iterator it = m_bestGoals.begin(); it != m_bestGoals.end(); ++it)
	{
		m_bestMap(*it) = '.';
		//cout << it->x << " " << it->y << " ";
	}

	for(std::set<Position>::iterator it = boxes.begin(); it != boxes.end(); ++it)
	{
		m_bestMap(*it) = (m_bestGoals.find(*it) == m_bestGoals.end()) ? '$' : '*';
	}

	m_bestMap(player) = (m_bestGoals.find(player) == m_bestGoals.end()) ? '@' : '+';

	m_map = m_bestMap;

	//cout << "finished!\n";
}

void LevelGenerator::printBest()
{
	for(int i = m_bestSolution.size()-1; i >= 0; --i)
	{
		Map temp = m_bestMap;

		Position player = m_bestSolution[i].getPlayerPos();

		std::set<Position> boxes = m_bestSolution[i].getBoxPos();

		for(std::set<Position>::iterator it = m_bestGoals.begin(); it != m_bestGoals.end(); ++it)
		{
			m_bestMap(*it) = '.';
		}

		for(std::set<Position>::iterator it = boxes.begin(); it != boxes.end(); ++it)
		{
			m_bestMap(*it) = (m_bestGoals.find(*it) == m_bestGoals.end()) ? '$' : '*';
		}

		m_bestMap(player) = (m_bestGoals.find(player) == m_bestGoals.end()) ? '@' : '+';

		std::cout << m_bestMap;
		m_bestMap = temp;
	}
}

void LevelGenerator::printMap() const
{
	std::cout << m_map;
}

int LevelGenerator::getMax() const
{
	return m_max;
}

string LevelGenerator::getSolution() const
{
	return m_solution;
}

const Position LevelGenerator::direction[] = { Position(1,0), Position(-1,0), Position(0,1), Position(0,-1) };
