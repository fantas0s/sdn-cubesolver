#ifndef PUZZLECONTAINER_H
#define PUZZLECONTAINER_H
#include "piecelocationcontainer.h"
#include <QVector>
#include <QString>

class PuzzleContainer
{
    friend class SDNCubeSolverTest;
public:
    PuzzleContainer(int width, int height, int depth);
    bool add(const PieceLocationContainer* pieceAndLocation);
    void pop();
    QString extractStepsToString();
private:
    PuzzleContainer();
    const int* getGrid();
    void addToGrid(const PieceLocationContainer *pieceAndLocation);
    void removeFromGrid(const PieceLocationContainer *pieceAndLocation);
    bool gridHasOverlaps();
    QVector<const PieceLocationContainer*> piecesInContainer;
    int myWidth;
    int myHeight;
    int myDepth;
    int gridLength;
    int* grid;
};

#endif // PUZZLECONTAINER_H
