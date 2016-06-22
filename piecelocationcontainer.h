#ifndef PIECELOCATIONCONTAINER_H
#define PIECELOCATIONCONTAINER_H
#include "puzzlepiece.h"
#include "coordinates.h"
#include <QObject>

class PieceLocationContainer
{
public:
    PieceLocationContainer(const PuzzlePiece *piece, const Coordinates *location);
    PieceLocationContainer() :
        myLocation(Q_NULLPTR){}
    const PuzzlePiece *piece() const;
    const Coordinates *location() const;
private:
    const PuzzlePiece* myPiece;
    const Coordinates* myLocation;
};

#endif // PIECELOCATIONCONTAINER_H
