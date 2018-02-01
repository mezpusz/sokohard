#pragma once

#include "util.h"

class Pattern
{
private:

    int n;				// height
    int m;				// width
    vector<char> tiles; 
    // a csempeket tartalmazo vektor

private:

    void rotate(Pattern& p, Rotation r);
    // p elforgatasa r szerint
    void reflect(Pattern& p);
    // p fuggoleges tukrozese
    // (vizszintes nem kell, mert 180 fokos forgatassal
    //  es fuggoleges tukrozessel eloallithato)
public:

    Pattern();
    void Initialize(int n, int m, string in);
    // adott n magassag es m szelesseg szerint in alapjan inic.
    void getPattern(Pattern& p, Rotation rotation, bool reflection);
    // p-be a rotation szerinti forgatas es reflection szerinti
    // tukrozessel eloallitja ennek a mintanak a masolatat
    vector<char>& getPatternAsVector() const;
    // vektorkent visszaadja a mintazatot
    
    bool match(Pattern p, Join j) const;
    // ezt az objektumot illeszkedes szempontjabol osszeveti p-vel
    char& operator()(int x, int y) const;
    bool operator==(const Pattern& rhs) const;
    bool operator<(const Pattern& rhs) const;
};
