#ifndef PUZZLECONTAINER_H
#define PUZZLECONTAINER_H
#include "piecelocationcontainer.h"
#include <Qvector>
#include <QString>

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
    int* renderPiecesToGrid();
    QVector<PieceLocationContainer> piecesInContainer;
    int myWidth;
    int myHeight;
    int myDepth;
};

#endif // PUZZLECONTAINER_H
