#ifndef CANVASPRINTER_HPP
#define CANVASPRINTER_HPP
#include <QString>
#include "piecelocationcontainer.h"
#include "printablepiece.h"

class CanvasPrinter
{
public:
    CanvasPrinter(int containerWidth, int containerHeight, int containerDepth);
    QString printEmptyGrid();
    QString printPieceBlocksToCanvas(const QString canvas, const PieceLocationContainer *pieceToPrint);
private:
    CanvasPrinter();
    int myWidth;
    int myHeight;
    int myDepth;
    QString createCombinedStringForDrawing(QVector<QString*> *drawArea);
    void drawXAxisLines(PrintablePiece piece, const Coordinates curr, QVector<QString*> drawArea);
    void drawYAxisLines(PrintablePiece piece, const Coordinates curr, QVector<QString*> drawArea);
    void drawZAxisLines(PrintablePiece piece, const Coordinates curr, QVector<QString*> drawArea);
    void drawBlockTop(PrintablePiece piece, const Coordinates curr, QVector<QString*> drawArea);
};

#endif // CANVASPRINTER_HPP
