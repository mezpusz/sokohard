#pragma once

#include <string>
#include <vector>

enum Rotation
{
    _0,
    _90,
    _180,
    _270
};

/*
 * NORTH_WEST | NORTH | NORTH_EAST
 * -----------*********-----------
 *    WEST    *pattern*   EAST
 * -----------*********-----------
 * SOUTH_WEST | SOUTH | SOUTH_EAST
 */
enum Join
{
    NORTH = 0x1,
    EAST = 0x2,
    SOUTH = 0x4,
    WEST = 0x8,
    NORTH_EAST = NORTH | EAST,
    SOUTH_EAST = SOUTH | EAST,
    SOUTH_WEST = SOUTH | WEST,
    NORTH_WEST = NORTH | WEST
};

class Pattern
{
public:
    Pattern() = default;
    void Initialize(int n, int m, std::string in);
    // adott n magassag es m szelesseg szerint in alapjan inic.
    Pattern getPattern(Rotation rotation, bool reflection);
    // p-be a rotation szerinti forgatas es reflection szerinti
    // tukrozessel eloallitja ennek a mintanak a masolatat
    const std::vector<char>& getPatternAsVector() const;
    // vektorkent visszaadja a mintazatot

    bool match(Pattern p, Join j) const;
    // ezt az objektumot illeszkedes szempontjabol osszeveti p-vel
    char& operator()(int x, int y) const;
    bool operator==(const Pattern& rhs) const;
    bool operator<(const Pattern& rhs) const;

private:
    void rotate(Pattern& p, Rotation r);
    // p elforgatasa r szerint
    void reflect(Pattern& p);
    // p fuggoleges tukrozese
    // (vizszintes nem kell, mert 180 fokos forgatassal
    //  es fuggoleges tukrozessel eloallithato)

    int n;				// height
    int m;				// width
    std::vector<char> tiles; 
    // a csempeket tartalmazo vektor
};
