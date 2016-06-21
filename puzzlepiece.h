#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
#include "pieceblock.h"
#include <QVector>

class PuzzlePiece
{
    friend class SDNCubeSolverTest;
public:
    PuzzlePiece();
    void addBlock(PieceBlock block);
    int numBlocks();
    QVector<PieceBlock> getBlockList();
    void rotate();
private:
    QVector<PieceBlock> myBlocks;
    bool blockFoundAt(const Coordinates location);
    int rotations;
};

#endif // PUZZLEPIECE_H
