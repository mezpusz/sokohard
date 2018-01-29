#include "Pattern.h"


Pattern::Pattern()
{
}

void Pattern::Initialize(int n, int m, string in)
{
	this->n = n;
	this->m = m;

	tiles.clear();

	for(int i = 0; i <= n+1; ++i)
	{
		for(int j = 0; j <= m+1; ++j)
		{
			tiles.push_back(in[i*(m+2) + j]);
		}
	}
}

void Pattern::getPattern(Pattern& p, ROTATION rotation, bool reflection)
{
	p = *this;

	rotate(p, rotation);
	
	if(reflection)
	{
		reflect(p);
	}
}

void Pattern::rotate(Pattern& p, ROTATION r)
{
	vector<char> v = p.getPatternAsVector();
	string s = "";

	switch(r)
	{
	case R0 : 
		return;
	case R90 :
		{
			for(int i = 0; i <= m+1; ++i)
			{
				for(int j = n+1; j >=0; --j)
				{
					s.push_back(v[j*(n+2) + i]);
				}
			}
			p.Initialize(m, n, s);
		} break;
	case R180 :
		{
			for(int i = n+1; i >= 0; --i)
			{
				for(int j = m+1; j >=0; --j)
				{
					s.push_back(v[i*(m+2) + j]);
				}
			}
			p.Initialize(n, m, s);
		} break;
	case R270 :
		{
			for(int i = m+1; i >= 0; --i)
			{
				for(int j = 0; j <= n+1; ++j)
				{
					s.push_back(v[j*(n+2) + i]);
				}
			}
			p.Initialize(m, n, s);
		}
	}
}

void Pattern::reflect(Pattern& p)
{
	vector<char> v = p.getPatternAsVector();
	string s = "";

	for(int i = 0; i <= n+1; ++i)
	{
		for(int j = m+1; j >= 0; --j)
		{
			s.push_back(v[i*(m+2) + j]);
		}
	}

	p.Initialize(n, m, s);
}

vector<char>& Pattern::getPatternAsVector() const
{
	return const_cast<vector<char>&>(tiles);
}

bool Pattern::match(Pattern p, JOIN j) const
{
	bool match = true;
	char t1;
	char t2;

	int stop = (j & (NORTH | SOUTH)) ? m+1 : n+1;

	int x1, x2, y1, y2;

	switch(j)
	{
	case NORTH :
	case SOUTH :
	case EAST :
	case WEST :
		{
			for(int i = 1; i < stop; ++i)
			{
				x1 = (j & WEST) ? 1 : ((j & EAST) ? m : i);
				x2 = (j & WEST) ? m+1 : ((j & EAST) ? 0 : i);
				y1 = (j & NORTH) ? 1 : ((j & SOUTH) ? n : i);
				y2 = (j & NORTH) ? n+1 : ((j & SOUTH) ? 0 : i);

				t1 = (*this)(x1,y1);
				t2 = p(x2,y2);

				if(t2 != '0' && t1 != t2)
				{
					match = false;
					break;
				}

				x1 = (j & WEST) ? 0 : ((j & EAST) ? m+1 : i);
				x2 = (j & WEST) ? m : ((j & EAST) ? 1 : i);
				y1 = (j & NORTH) ? 0 : ((j & SOUTH) ? n+1 : i);
				y2 = (j & NORTH) ? n : ((j & SOUTH) ? 1 : i);

				t1 = (*this)(x1,y1);
				t2 = p(x2,y2);

				if(t1 != '0' && t1 != t2)
				{
					match = false;
					break;
				}
			}
		} break;
	case NORTH_EAST :
	case SOUTH_EAST :
	case SOUTH_WEST :
	case NORTH_WEST :
		{
			x1 = (j & EAST) ? m : 1;
			x2 = (j & EAST) ? 0 : m+1;
			y1 = (j & NORTH) ? 1 : n;
			y2 = (j & NORTH) ? n+1 : 0;

			t1 = (*this)(x1,y1);
			t2 = p(x2,y2);

			if(t2 != '0' && t1 != t2)
				match = false;

			x1 = (j & EAST) ? m+1 : 0;
			x2 = (j & EAST) ? 1 : m;
			y1 = (j & NORTH) ? 0 : n+1;
			y2 = (j & NORTH) ? n : 1;

			t1 = (*this)(x1,y1);
			t2 = p(x2,y2);

			if(t1 != '0' && t1 != t2)
				match = false;
		} break;
	}

	return match;
}

char& Pattern::operator()(int x, int y) const
{
	return const_cast<char&>(tiles[y*(m+2) + x]);
}

bool Pattern::operator==(const Pattern& rhs) const
{
	return (tiles == rhs.getPatternAsVector());
}

bool Pattern::operator<(const Pattern& rhs) const
{
	return (tiles < rhs.getPatternAsVector());
}