#include "puzzlepiece.h"

PuzzlePiece::PuzzlePiece()
{
}

void PuzzlePiece::addBlock(PieceBlock* block)
{
    myBlocks.append(block);
}

int PuzzlePiece::numBlocks()
{
    return myBlocks.length();
}

QVector<PieceBlock*> PuzzlePiece::getBlockList()
{
    return myBlocks;
}
