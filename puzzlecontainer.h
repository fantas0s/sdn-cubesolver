#ifndef PUZZLECONTAINER_H
#define PUZZLECONTAINER_H
#include "puzzlepiece.h"

class PuzzleContainer
{
    friend class SDNCubeSolverTest;
public:
    PuzzleContainer(int width, int height, int depth);
    bool add(PuzzlePiece piece, Coordinates location);
private:
    PuzzleContainer();
    void renderPiecesToGrid();
    QVector<PuzzlePiece> pieces;
    int myWidth;
    int myHeight;
    int myDepth;
};

#endif // PUZZLECONTAINER_H
