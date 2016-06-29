#include "puzzlepiece.h"
#include <QDebug>

PuzzlePiece::PuzzlePiece() :
    myBlockCount(0),
    xRotations(0),
    yRotations(0),
    zRotations(0)
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
    if(myBlockCount >= MAX_BLOCKS)
    {
        qDebug() << "too many blocks added!";
        return;
    }
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
    if( zRotations < 4 )
    {
        for (int i = 0; i < myBlockCount ; ++i)
        {
            const Coordinates *curr = myBlocks[i].coords();
            myBlocks[i].updateCoordinates(curr->y, -1*curr->x, curr->z);
        }
        zRotations++;
    }
    if( zRotations >= 4 )
    {
        if( yRotations < 4)
        {
            for (int i = 0; i < myBlockCount ; ++i)
            {
                const Coordinates *curr = myBlocks[i].coords();
                myBlocks[i].updateCoordinates(curr->z, curr->y, -1*curr->x);
            }
            yRotations++;
        }
        if( yRotations >= 4 )
        {
            if( xRotations < 4)
            {
                for (int i = 0; i < myBlockCount ; ++i)
                {
                    const Coordinates *curr = myBlocks[i].coords();
                    myBlocks[i].updateCoordinates(curr->x, curr->z, -1*curr->y);
                }
                xRotations++;
            }
            if( xRotations >= 4 )
            {
                xRotations = 0;
                yRotations = 0;
                zRotations = 0;
            }
        }
    }
}
