#include "piecelocationcontainer.h"

PieceLocationContainer::PieceLocationContainer(const PuzzlePiece *piece, const Coordinates *location) :
    myLocation(location->x, location->y, location->z)
{
    myPiece = *piece;
}

const PuzzlePiece *PieceLocationContainer::piece()
{
    return &myPiece;
}

const Coordinates *PieceLocationContainer::location()
{
    return &myLocation;
}
