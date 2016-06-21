#ifndef PRINTABLEPIECE_H
#define PRINTABLEPIECE_H
#include "piecelocationcontainer.h"
#include "printableblock.h"
#include <QVector>

class PrintablePiece
{
public:
    PrintablePiece(PieceLocationContainer origin);
    QVector<PrintableBlock> getBlockList();
    bool noBlockAt(Coordinates location);
private:
    void addBlock(PieceBlock block);
    QVector<PrintableBlock> myFixedBlocks;
};

#endif // PRINTABLEPIECE_H
