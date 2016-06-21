#ifndef PRINTABLEBLOCK_H
#define PRINTABLEBLOCK_H
#include "pieceblock.h"

class PrintableBlock : public PieceBlock
{
public:
    PrintableBlock(PieceBlock origin);
    PrintableBlock();
    bool notPrinted() const;
    void setPrinted();
private:
    bool printed;
};

#endif // PRINTABLEBLOCK_H
