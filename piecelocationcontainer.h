#ifndef PIECELOCATIONCONTAINER_H
#define PIECELOCATIONCONTAINER_H
#include "puzzlepiece.h"
#include "coordinates.h"

class PieceLocationContainer
{
public:
    PieceLocationContainer(const PuzzlePiece *piece, const Coordinates *location);
    PieceLocationContainer() :
        myLocation(0,0,0){}
    const PuzzlePiece *piece();
    const Coordinates *location();
private:
    PuzzlePiece myPiece;
    Coordinates myLocation;
};

#endif // PIECELOCATIONCONTAINER_H
