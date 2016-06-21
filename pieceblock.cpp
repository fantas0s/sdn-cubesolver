#include "pieceblock.h"

PieceBlock::PieceBlock() :
    myCoordinates(0,0,0)
{
}

PieceBlock::PieceBlock(int x, int y, int z) :
    myCoordinates(x, y, z)
{
}

Coordinates PieceBlock::coords() const
{
    return myCoordinates;
}

void PieceBlock::updateCoordinates(int x, int y, int z)
{
    myCoordinates = Coordinates(x,y,z);
}
