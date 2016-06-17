#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
#include "pieceblock.h"
#include <QVector>

class PuzzlePiece
{
public:
    void addBlock(PieceBlock block);
    int numBlocks();
    bool noBlockAt(Coordinates location);
    QVector<PieceBlock> getBlockList();
private:
    QVector<PieceBlock> myBlocks;
    bool blockFoundAt(const Coordinates location);
};

#endif // PUZZLEPIECE_H
