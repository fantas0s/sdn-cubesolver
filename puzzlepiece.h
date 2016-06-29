#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H
#include "pieceblock.h"
#define MAX_BLOCKS 7

class PuzzlePiece
{
    friend class SDNCubeSolverTest;
public:
    PuzzlePiece();
    void addBlock(PieceBlock block);
    int numBlocks() const;
    const PieceBlock* getBlockList() const;
    void rotate();
private:
    PieceBlock myBlocks[MAX_BLOCKS];
    int myBlockCount;
    bool blockFoundAt(const Coordinates location);
    int xRotations;
    int yRotations;
    int zRotations;
};

#endif // PUZZLEPIECE_H
