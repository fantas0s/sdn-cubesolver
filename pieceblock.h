#ifndef PIECEBLOCK_H
#define PIECEBLOCK_H
#include "coordinates.h"

class PieceBlock
{
public:
    PieceBlock();
    PieceBlock(int x, int y, int z);
    Coordinates coords() const;
private:
    Coordinates myCoordinates;
};

#endif // PIECEBLOCK_H
