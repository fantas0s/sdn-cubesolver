#ifndef PIECECREATOR_H
#define PIECECREATOR_H
#include "puzzlepiece.h"

class PieceCreator
{
public:
    static void createPieceOrangePlus(PuzzlePiece* writeLocation);
    static void createPieceBlue3DTetris(PuzzlePiece* writeLocation);
    static void createPieceBlackClothHanger(PuzzlePiece* writeLocation);
    static void createPieceOrangeDoubleL(PuzzlePiece* writeLocation);
    static void createPieceOrangeJigsawUp1(PuzzlePiece* writeLocation);
    static void createPieceOrangeJigsawUp2(PuzzlePiece* writeLocation);
    static void createPieceBlackLeveledT(PuzzlePiece* writeLocation);
    static void createPieceBlackKnobUpT(PuzzlePiece* writeLocation);
    static void createPieceBlackZigZag(PuzzlePiece* writeLocation);
    static void createPieceBlue3DL(PuzzlePiece* writeLocation);
    static void createPieceBlueDoubleL(PuzzlePiece* writeLocation);
    static void createPieceBlueFlatZigZag(PuzzlePiece* writeLocation);
    static void createPieceBlueLittleL(PuzzlePiece* writeLocation);
};

#endif // PIECECREATOR_H
