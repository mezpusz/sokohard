#include "map.h"

void Map::init(int width, int height, char c)
{
    m_width = width;
    m_height = height;
    m_map.resize(width*height, '0');
}

void Map::init(int width, int height, vector<char> in)
{
    m_width = width;
    m_height = height;
    m_map.clear();
    m_map.insert(m_map.begin(), in.begin(), in.end());
}

char& Map::operator()(int x, int y) const
{
    return const_cast<char&>(m_map[y*m_width + x]);
}

char& Map::operator()(int x, int y)
{
    return m_map[y*m_width + x];
}

char& Map::operator()(Position p) const
{
    return const_cast<char&>(m_map[p.y*m_width + p.x]);
}

char& Map::operator()(Position p)
{
    return m_map[p.y*m_width + p.x];
}

vector<char>& Map::getMap()
{
    return m_map;
}

vector<char>::iterator Map::begin()
{
    return m_map.begin();
}

vector<char>::iterator Map::end()
{
    return m_map.end();
}

int Map::width() const 
{
    return m_width;
}

int Map::height() const 
{
    return m_height;
}

void Map::printMap() const
{
    cout << '\n';
    for(int i = 0; i < m_width + 2; ++i)
    {
        cout << '#';
    }
    cout << '\n';
    for(int j = 0; j < m_height; ++j)
    {
        cout << '#';
        for(int i = 0; i < m_width; ++i)
        {
            cout << operator()(i,j);
        }
        cout << '#';
        cout << '\n';
    }

    for(int i = 0; i < m_width + 2; ++i)
    {
        cout << '#';
    }
    cout << '\n';
    cout << '\n';
}
