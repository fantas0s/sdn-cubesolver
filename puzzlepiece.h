#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
#include "pieceblock.h"
#include <QVector>
#define MAX_BLOCKS 5

class PuzzlePiece
{
    friend class SDNCubeSolverTest;
public:
    PuzzlePiece();
    void addBlock(PieceBlock block);
    int numBlocks();
    PieceBlock* getBlockList();
    void rotate();
private:
    PieceBlock myBlocks[MAX_BLOCKS];
    int myBlockCount;
    bool blockFoundAt(const Coordinates location);
    int rotations;
};

#endif // PUZZLEPIECE_H
