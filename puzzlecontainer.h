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
    const int* getGrid();
    void addToGrid(PieceLocationContainer *pieceAndLocation);
    void removeFromGrid(PieceLocationContainer *pieceAndLocation);
    bool gridHasOverlaps();
    QVector<PieceLocationContainer> piecesInContainer;
    int myWidth;
    int myHeight;
    int myDepth;
    int gridLength;
    int* grid;
};

#endif // PUZZLECONTAINER_H
