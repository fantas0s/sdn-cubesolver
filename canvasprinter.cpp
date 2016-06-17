#include "canvasprinter.hpp"

CanvasPrinter::CanvasPrinter(int containerWidth, int containerHeight, int containerDepth) :
    myWidth(containerWidth),
    myHeight(containerHeight),
    myDepth(containerDepth)
{
}



QString CanvasPrinter::createCombinedStringForDrawing(QVector<QString*> *drawArea)
{
    QString returnString;
     while( !drawArea->isEmpty() )
     {
         QString* stringToDelete = drawArea->at(0);
         drawArea->removeFirst();
         returnString += stringToDelete;
         returnString += QString("\n");
         delete stringToDelete;
     }
     return returnString;
}

QString CanvasPrinter::printEmptyGrid()
{
    int rowsToDraw = myWidth + myHeight + myDepth;
    QVector<QString*> drawArea;
    for( int row = 0 ; row < rowsToDraw ; ++row )
    {
        QString* stringToAdd = new QString();
        while( stringToAdd->length() < (((myWidth+myHeight)*2)+1) )
        {
            *stringToAdd += " ";
        }
        drawArea.append(stringToAdd);
    }
    for( int depthCounter = 0 ; depthCounter < myDepth ; ++depthCounter )
    {
        QString* rowForAdd = drawArea[depthCounter];
        (*rowForAdd)[((myWidth-1)*2)+2] = '|';
        rowForAdd = drawArea[depthCounter+myWidth];
                (*rowForAdd)[0] = '|';
        rowForAdd = drawArea[depthCounter+myHeight];
                (*rowForAdd)[rowForAdd->length()-1] = '|';
    }
    for( int widthCounter = 0 ; widthCounter < myWidth ; ++widthCounter )
    {
        QString* rowForAdd = drawArea[widthCounter];
        (*rowForAdd)[((myWidth-(widthCounter+1))*2)+1] = '/';
        rowForAdd = drawArea[widthCounter+myHeight+myDepth];
                (*rowForAdd)[rowForAdd->length()-(widthCounter*2)-2] = '/';
        rowForAdd = drawArea[widthCounter+myDepth];
                (*rowForAdd)[((myWidth-1-widthCounter)*2)+1] = '/';
    }
    for( int heightCounter = 0 ; heightCounter < myHeight ; ++heightCounter )
    {
        QString* rowForAdd = drawArea[heightCounter];
        (*rowForAdd)[((myWidth-1)*2)+3+(heightCounter*2)] = '\\';
        rowForAdd = drawArea[heightCounter+myWidth+myDepth];
                (*rowForAdd)[(heightCounter*2)+1] = '\\';
        rowForAdd = drawArea[heightCounter+myDepth];
                (*rowForAdd)[((myWidth+heightCounter-1)*2)+3] = '\\';
    }
    return createCombinedStringForDrawing(&drawArea);
}

void CanvasPrinter::drawXAxisLines(Coordinates location, PuzzlePiece piece, Coordinates curr, QVector<QString*> drawArea)
{
    const int realX = curr.x+location.x;
    const int realY = curr.y+location.y;
    const int realZ = curr.z+location.z;
    if( piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z+1)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) == piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z)) ) )
    {
        const int rowOfTopLeftEdge = myDepth-realZ+realX+realY;
        const int charIndexOfTopLeftEdge = ((myWidth-1)*2)+3-((realX-realY)*2);
        (*drawArea[rowOfTopLeftEdge])[charIndexOfTopLeftEdge] = '/';
    }
    if( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) == piece.noBlockAt(Coordinates(curr.x, curr.y-1, curr.z+1)) ) )
    {
        const int rowOfBackLeftEdge = myDepth-realZ+realX+realY-1;
        const int charIndexOfBackLeftEdge = ((myWidth-1)*2)+1-((realX-realY)*2);
        (*drawArea[rowOfBackLeftEdge])[charIndexOfBackLeftEdge] = '/';
    }
    if( piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z-1)) == piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z-1)) ) )
    {
        const int rowOfBottomleftEdge = myDepth-realZ+realX+realY+1;
        const int charIndexOfBottomLeftEdge = ((myWidth-1)*2)+3-((realX-realY)*2);
        (*drawArea[rowOfBottomleftEdge])[charIndexOfBottomLeftEdge] = '/';
    }
}

void CanvasPrinter::drawYAxisLines(Coordinates location, PuzzlePiece piece, Coordinates curr, QVector<QString*> drawArea)
{
    const int realX = curr.x+location.x;
    const int realY = curr.y+location.y;
    const int realZ = curr.z+location.z;
    if( piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z+1)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) == piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z)) ) )
    {
        const int rowOfTopRightEdge = myDepth-realZ+realX+realY;
        const int charIndexOfTopRightEdge = ((myWidth-1)*2)+1-((realX-realY)*2);
        (*drawArea[rowOfTopRightEdge])[charIndexOfTopRightEdge] = '\\';
    }
    if( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) == piece.noBlockAt(Coordinates(curr.x-1, curr.y, curr.z+1)) ) )
    {
        const int rowOfBackRightEdge = myDepth-realZ+realX+realY-1;
        const int charIndexOfBackRightEdge = ((myWidth-1)*2)+3-((realX-realY)*2);
        (*drawArea[rowOfBackRightEdge])[charIndexOfBackRightEdge] = '\\';
    }
    if( piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z-1)) == piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z-1)) ) )
    {
        const int rowOfBottomleftEdge = myDepth-realZ+realX+realY+1;
        const int charIndexOfBottomLeftEdge = ((myWidth-1)*2)+1-((realX-realY)*2);
        (*drawArea[rowOfBottomleftEdge])[charIndexOfBottomLeftEdge] = '\\';
    }
}

void CanvasPrinter::drawZAxisLines(Coordinates location, PuzzlePiece piece, Coordinates curr, QVector<QString*> drawArea)
{
    const int realX = curr.x+location.x;
    const int realY = curr.y+location.y;
    const int realZ = curr.z+location.z;
    if( piece.noBlockAt(Coordinates(curr.x+1, curr.y+1, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z)) == piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z)) ) )
    {
        const int rowOfBlockFront = myDepth-realZ+realX+realY+1;
        const int charIndexOfBlockFront = ((myWidth-1)*2)+2-((realX-realY)*2);
        (*drawArea[rowOfBlockFront])[charIndexOfBlockFront] = '|';
    }
    if( piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y-1, curr.z)) || (!piece.noBlockAt(Coordinates(curr.x+1, curr.y-1, curr.z))) ) )
    {
        const int rowOfBlockLeft = myDepth-realZ+realX+realY;
        const int charIndexOfBlockLeft = ((myWidth-1)*2)-((realX-realY)*2);
        (*drawArea[rowOfBlockLeft])[charIndexOfBlockLeft] = '|';
    }
    if( piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x-1, curr.y, curr.z)) || (!piece.noBlockAt(Coordinates(curr.x-1, curr.y+1, curr.z))) ) )
    {
        const int rowOfBlockRight = myDepth-realZ+realX+realY;
        const int charIndexOfBlockRight = ((myWidth-1)*2)+4-((realX-realY)*2);
        (*drawArea[rowOfBlockRight])[charIndexOfBlockRight] = '|';
    }
}

void CanvasPrinter::drawBlockTop(Coordinates location, PuzzlePiece piece, Coordinates curr, QVector<QString*> drawArea)
{
    const int realX = curr.x+location.x;
    const int realY = curr.y+location.y;
    const int realZ = curr.z+location.z;
    if( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) )
    {
        const int charIndexOfBlockTop = ((myWidth-1)*2)+2-((realX-realY)*2);
        int rowOfBlockTop = myDepth-realZ+realX+realY;
        (*drawArea[rowOfBlockTop])[charIndexOfBlockTop] = ' ';
        rowOfBlockTop = myDepth-realZ+realX+realY-1;
        (*drawArea[rowOfBlockTop])[charIndexOfBlockTop] = ' ';
    }
}

QString CanvasPrinter::printPieceBlocksToCanvas(const QString canvas, PieceLocationContainer pieceToPrint)
{
    int rowsToDraw = myWidth + myHeight + myDepth;
    QVector<QString*> drawArea;
    for( int row = 0 ; row < rowsToDraw ; ++row )
    {
        drawArea.append(new QString(canvas.section('\n',row,row)));
    }

    PuzzlePiece piece = pieceToPrint.piece();
    Coordinates location = pieceToPrint.location();
    QVector<PieceBlock> pieceBlocks = piece.getBlockList();
    for (int blockIndex = 0 ; blockIndex < pieceBlocks.length() ; ++blockIndex )
    {
        // Only draw three sides for a cube, rest are hidden.
        // Do not draw line if block continues to that direction
        Coordinates curr = pieceBlocks.at(blockIndex).coords();
        drawXAxisLines(location, piece, curr, drawArea);
        drawYAxisLines(location, piece, curr, drawArea);
        drawZAxisLines(location, piece, curr, drawArea);
        drawBlockTop(location, piece, curr, drawArea);
    }
    return createCombinedStringForDrawing(&drawArea);
}
