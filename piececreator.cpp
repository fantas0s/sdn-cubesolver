#include "piececreator.h"

void PieceCreator::createPieceOrangePlus(PuzzlePiece* writeLocation)
{
    //orange Plus
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(1,2,0));
    *writeLocation = piece;
}

void PieceCreator::createPieceBlue3DTetris(PuzzlePiece* writeLocation)
{
    // blue 3D tetris piece
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,0,1));
    *writeLocation = piece;
}

void PieceCreator::createPieceBlackClothHanger(PuzzlePiece* writeLocation)
{
    // black cloth hanger
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    *writeLocation = piece;
}

void PieceCreator::createPieceOrangeDoubleL(PuzzlePiece* writeLocation)
{
    //orange double-L
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(0,0,2));
    *writeLocation = piece;
}

void PieceCreator::createPieceOrangeJigsawUp1(PuzzlePiece* writeLocation)
{
    //orange jigsaw with up-part at end
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(2,1,1));
    *writeLocation = piece;
}

void PieceCreator::createPieceOrangeJigsawUp2(PuzzlePiece* writeLocation)
{
    //orange jigsaw with up-part before the end
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    *writeLocation = piece;
}

void PieceCreator::createPieceBlackLeveledT(PuzzlePiece* writeLocation)
{
    // black T-like with end knob in level with rest of it
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,-1,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    *writeLocation = piece;
}

void PieceCreator::createPieceBlackKnobUpT(PuzzlePiece* writeLocation)
{
    // black T-like with end knob up
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    *writeLocation = piece;
}

void PieceCreator::createPieceBlackZigZag(PuzzlePiece* writeLocation)
{
    // black zigzag
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    piece.addBlock(PieceBlock(2,1,1));
    *writeLocation = piece;
}

void PieceCreator::createPieceBlue3DL(PuzzlePiece* writeLocation)
{
    // blue 3D'ish L
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,1,1));
    *writeLocation = piece;
}

void PieceCreator::createPieceBlueDoubleL(PuzzlePiece* writeLocation)
{
    // blue double-L
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(2,1,0));
    *writeLocation = piece;
}

void PieceCreator::createPieceBlueFlatZigZag(PuzzlePiece* writeLocation)
{
    // blue flat zigzag
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(2,2,0));
    *writeLocation = piece;
}

void PieceCreator::createPieceBlueLittleL(PuzzlePiece* writeLocation)
{
    // blue little L
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    *writeLocation = piece;
}
