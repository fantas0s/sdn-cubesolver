#ifndef PIECEBLOCK_H
#define PIECEBLOCK_H
#include "coordinates.h"

class PieceBlock
{
public:
    PieceBlock();
    PieceBlock(int x, int y, int z);
    const Coordinates *coords() const;
    void updateCoordinates(int x, int y, int z);
private:
    Coordinates myCoordinates;
};

#endif // PIECEBLOCK_H
