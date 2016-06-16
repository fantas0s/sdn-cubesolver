#include "piecelocationcontainer.h"

PieceLocationContainer::PieceLocationContainer(PuzzlePiece piece, Coordinates location) :
    myLocation(location.x, location.y, location.z)
{
    myPiece = piece;
}

PuzzlePiece PieceLocationContainer::piece()
{
    return myPiece;
}

Coordinates PieceLocationContainer::location()
{
    return myLocation;
}
