#ifndef PIECEBLOCK_H
#define PIECEBLOCK_H
#include <QVector>

class PieceBlock
{
public:
    PieceBlock(int x, int y, int z);
    QVector<int> coords();
private:
    PieceBlock(){}
};

#endif // PIECEBLOCK_H
