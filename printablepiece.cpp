#include "printablepiece.h"

PrintablePiece::PrintablePiece(const PieceLocationContainer *origin)
{
    const PieceBlock* blockList = origin->piece()->getBlockList();
    for (int i = 0 ; i < origin->piece()->numBlocks() ; ++i )
    {
        addBlock(PieceBlock(blockList[i].coords()->x + origin->location()->x,
                            blockList[i].coords()->y + origin->location()->y,
                            blockList[i].coords()->z + origin->location()->z));
    }
}

void PrintablePiece::addBlock(PieceBlock block)
{
    PrintableBlock blockToAdd(block);
    myFixedBlocks.append(blockToAdd);
}

bool PrintablePiece::noBlockAt(Coordinates location)
{
    bool blockFound = false;
    QVector<PrintableBlock>::iterator i;
    for (i = myFixedBlocks.begin(); i != myFixedBlocks.end(); ++i)
    {
        if( *((*i).coords()) == location )
        {
            blockFound = true;
            break;
        }
    }
    return !blockFound;
}

QVector<PrintableBlock> PrintablePiece::getBlockList()
{
    return myFixedBlocks;
}
