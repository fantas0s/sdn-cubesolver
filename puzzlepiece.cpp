#include "puzzlepiece.h"
#include <QDebug>

PuzzlePiece::PuzzlePiece() :
    rotations(0)
{
}

bool PuzzlePiece::blockFoundAt(const Coordinates location)
{
    bool blockFound = false;
    QVector<PieceBlock>::iterator i;
    for (i = myBlocks.begin(); i != myBlocks.end(); ++i)
    {
        if( (*i).coords() == location )
        {
            blockFound = true;
            break;
        }
    }
    return blockFound;
}

void PuzzlePiece::addBlock(PieceBlock block)
{
    if( blockFoundAt(block.coords()) )
    {
        qDebug() << "Duplicate block at coordinates" << block.coords().x << "," << block.coords().y << "," << block.coords().z << "- deleting it.";
    }
    else
    {
        myBlocks.append(block);
    }
}

int PuzzlePiece::numBlocks()
{
    return myBlocks.length();
}

QVector<PieceBlock> PuzzlePiece::getBlockList()
{
    return myBlocks;
}

void PuzzlePiece::rotate()
{
    if( rotations < 4 )
    {
        QVector<PieceBlock> newBlockList;
        QVector<PieceBlock>::iterator i;
        for (i = myBlocks.begin(); i != myBlocks.end(); ++i)
        {
            Coordinates curr = i->coords();
            newBlockList.append(PieceBlock(curr.y, -1*curr.x, curr.z));
        }
        myBlocks = newBlockList;
    }
    if( (3 == rotations) ||
        (5 == rotations) )
    {
        // 90 degrees around X-axis
        QVector<PieceBlock> newBlockList;
        QVector<PieceBlock>::iterator i;
        for (i = myBlocks.begin(); i != myBlocks.end(); ++i)
        {
            Coordinates curr = i->coords();
            newBlockList.append(PieceBlock(curr.x, -1*curr.z, curr.y));
        }
        myBlocks = newBlockList;
    }
    else if( 4 == rotations)
    {
        // 180 degrees around X-axis
        QVector<PieceBlock> newBlockList;
        QVector<PieceBlock>::iterator i;
        for (i = myBlocks.begin(); i != myBlocks.end(); ++i)
        {
            Coordinates curr = i->coords();
            newBlockList.append(PieceBlock(curr.x, -1*curr.y, -1*curr.z));
        }
        myBlocks = newBlockList;
    }
    rotations++;
    if( rotations > 5 )
    {
        rotations = 0;
    }
}
