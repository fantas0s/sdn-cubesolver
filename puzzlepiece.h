#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
#include "pieceblock.h"
#include <QVector>

class PuzzlePiece
{
public:
    void addBlock(PieceBlock block);
    int numBlocks();
    QVector<PieceBlock> getBlockList();
private:
    QVector<PieceBlock> myBlocks;
};

#endif // PUZZLEPIECE_H
