#ifndef PIECELOCATIONCONTAINER_H
#define PIECELOCATIONCONTAINER_H
#include "puzzlepiece.h"
#include "coordinates.h"

class PieceLocationContainer
{
public:
    PieceLocationContainer(PuzzlePiece piece, Coordinates location);
    PieceLocationContainer() :
        myLocation(0,0,0){}
    PuzzlePiece piece();
    Coordinates location();
private:
    PuzzlePiece myPiece;
    Coordinates myLocation;
};

#endif // PIECELOCATIONCONTAINER_H
