#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
#include "pieceblock.h"

class PuzzlePiece
{
public:
    PuzzlePiece();
    void addBlock(PieceBlock* block);
    int numBlocks();
    QVector<PieceBlock*> getBlockList();
private:
    QVector<PieceBlock*> myBlocks;
};

#endif // PUZZLEPIECE_H
