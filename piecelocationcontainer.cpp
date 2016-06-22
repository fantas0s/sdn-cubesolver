#include "piecelocationcontainer.h"

PieceLocationContainer::PieceLocationContainer(const PuzzlePiece *piece, const Coordinates *location)
{
    myLocation = location;
    myPiece = piece;
}

const PuzzlePiece *PieceLocationContainer::piece() const
{
    return myPiece;
}

const Coordinates *PieceLocationContainer::location() const
{
    return myLocation;
}
