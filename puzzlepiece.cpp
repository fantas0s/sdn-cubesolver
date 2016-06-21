#include "puzzlepiece.h"
#include <QDebug>

PuzzlePiece::PuzzlePiece() :
    myBlockCount(0),
    rotations(0)
{
}

bool PuzzlePiece::blockFoundAt(const Coordinates location)
{
    bool blockFound = false;
    for (int i = 0; i < myBlockCount ; ++i)
    {
        if( *(myBlocks[i].coords()) == location )
        {
            blockFound = true;
            break;
        }
    }
    return blockFound;
}

void PuzzlePiece::addBlock(PieceBlock block)
{
    Q_ASSERT(myBlockCount < MAX_BLOCKS);
    if( blockFoundAt(*block.coords()) )
    {
        qDebug() << "Duplicate block at coordinates" << block.coords()->x << "," << block.coords()->y << "," << block.coords()->z << "- deleting it.";
    }
    else
    {
        myBlocks[myBlockCount] = block;
        myBlockCount++;
    }
}

int PuzzlePiece::numBlocks() const
{
    return myBlockCount;
}

const PieceBlock* PuzzlePiece::getBlockList() const
{
    return myBlocks;
}

void PuzzlePiece::rotate()
{
    if( rotations < 4 )
    {
        for (int i = 0; i < myBlockCount ; ++i)
        {
            const Coordinates *curr = myBlocks[i].coords();
            myBlocks[i].updateCoordinates(curr->y, -1*curr->x, curr->z);
        }
    }
    if( (3 == rotations) ||
        (5 == rotations) )
    {
        // 90 degrees around X-axis
        for (int i = 0; i < myBlockCount ; ++i)
        {
            const Coordinates *curr = myBlocks[i].coords();
            myBlocks[i].updateCoordinates(curr->x, -1*curr->z, curr->y);
        }
    }
    else if( 4 == rotations)
    {
        // 180 degrees around X-axis
        for (int i = 0; i < myBlockCount ; ++i)
        {
            const Coordinates *curr = myBlocks[i].coords();
            myBlocks[i].updateCoordinates(curr->x, -1*curr->y, -1*curr->z);
        }
    }
    rotations++;
    if( rotations > 5 )
    {
        rotations = 0;
    }
}
