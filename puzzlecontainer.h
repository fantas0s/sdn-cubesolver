#ifndef PUZZLECONTAINER_H
#define PUZZLECONTAINER_H
#include "piecelocationcontainer.h"

class PuzzleContainer
{
    friend class SDNCubeSolverTest;
public:
    PuzzleContainer(int width, int height, int depth);
    bool add(PieceLocationContainer pieceAndLocation);
    void pop();
    QString printSteps();
private:
    PuzzleContainer();
    QString printEmptyGrid();
    int* renderPiecesToGrid();
    QVector<PieceLocationContainer> piecesInContainer;
    int myWidth;
    int myHeight;
    int myDepth;
};

#endif // PUZZLECONTAINER_H
