#include "printablepiece.h"

PrintablePiece::PrintablePiece(PieceLocationContainer origin)
{
    QVector<PieceBlock> blockVector = origin.piece().getBlockList();
    QVector<PieceBlock>::iterator i;
    for (i = blockVector.begin(); i != blockVector.end(); ++i)
    {
        addBlock(PieceBlock(i->coords().x + origin.location().x,
                            i->coords().y + origin.location().y,
                            i->coords().z + origin.location().z));
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
        if( (*i).coords() == location )
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
