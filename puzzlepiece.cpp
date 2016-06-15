#include "puzzlepiece.h"
#include <QDebug>

void PuzzlePiece::addBlock(PieceBlock block)
{
    bool blockIsDuplicate = false;

    QVector<PieceBlock>::iterator i;
    for (i = myBlocks.begin(); i != myBlocks.end(); ++i)
    {
        if( (*i).coords() == block.coords() )
        {
            blockIsDuplicate = true;
            break;
        }
    }
    if( blockIsDuplicate )
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
