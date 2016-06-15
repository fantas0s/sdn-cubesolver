#include "puzzlecontainer.h"

PuzzleContainer::PuzzleContainer(int width, int height, int depth) :
    myWidth(width),
    myHeight(height),
    myDepth(depth)
{
}


void PuzzleContainer::renderPiecesToGrid()
{

}

bool PuzzleContainer::add(PuzzlePiece piece, Coordinates location)
{
    bool doesNotFit = false;
    QVector<PieceBlock> pieceBlocks = piece.getBlockList();
    QVector<PieceBlock>::iterator i;
    for (i = pieceBlocks.begin(); i != pieceBlocks.end(); ++i)
    {
        if( ((*i).coords().x + location.x < 0) ||
            ((*i).coords().x + location.x >= myWidth) ||
            ((*i).coords().y + location.y < 0) ||
            ((*i).coords().y + location.y >= myHeight) ||
            ((*i).coords().z + location.z < 0) ||
            ((*i).coords().z + location.z >= myDepth) )
        {
            doesNotFit = true;
            break;
        }
    }
    if( false == doesNotFit )
    {
        pieces.append(piece);
        renderPiecesToGrid();
    }

    return !doesNotFit;
}
