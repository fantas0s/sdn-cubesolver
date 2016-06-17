#ifndef CANVASPRINTER_HPP
#define CANVASPRINTER_HPP
#include <QString>
#include "piecelocationcontainer.h"
class CanvasPrinter
{
public:
    CanvasPrinter(int containerWidth, int containerHeight, int containerDepth);
    QString printEmptyGrid();
    QString printPieceBlocksToCanvas(const QString canvas, PieceLocationContainer pieceToPrint);
private:
    CanvasPrinter();
    int myWidth;
    int myHeight;
    int myDepth;
    QString createCombinedStringForDrawing(QVector<QString*> *drawArea);
    void drawXAxisLines(Coordinates location, PuzzlePiece piece, Coordinates curr, QVector<QString*> drawArea);
    void drawYAxisLines(Coordinates location, PuzzlePiece piece, Coordinates curr, QVector<QString*> drawArea);
    void drawZAxisLines(Coordinates location, PuzzlePiece piece, Coordinates curr, QVector<QString*> drawArea);
    void drawBlockTop(Coordinates location, PuzzlePiece piece, Coordinates curr, QVector<QString*> drawArea);
};

#endif // CANVASPRINTER_HPP
