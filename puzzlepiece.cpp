#include "puzzlepiece.h"
#include <QDebug>

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

bool PuzzlePiece::noBlockAt(Coordinates location)
{
    return !blockFoundAt(location);
}

QVector<PieceBlock> PuzzlePiece::getBlockList()
{
    return myBlocks;
}
