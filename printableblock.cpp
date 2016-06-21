#include "printableblock.h"

PrintableBlock::PrintableBlock(PieceBlock origin) :
    PieceBlock(origin.coords().x, origin.coords().y, origin.coords().z),
    printed(false)
{
}

PrintableBlock::PrintableBlock()
{
}

bool PrintableBlock::notPrinted() const
{
    return !printed;
}

void PrintableBlock::setPrinted()
{
    printed = true;
}
