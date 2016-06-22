#include "canvasprinter.hpp"
#include "printablepiece.h"

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

void CanvasPrinter::drawXAxisLines(PrintablePiece piece, const Coordinates curr, QVector<QString*> drawArea)
{
    if( piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z+1)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) == piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z)) ) )
    {
        const int rowOfTopRightEdge = myDepth-curr.z+curr.x+curr.y;
        const int charIndexOfTopRightEdge = ((myWidth-1)*2)+3-((curr.x-curr.y)*2);
        (*drawArea[rowOfTopRightEdge])[charIndexOfTopRightEdge] = '/';
    }
    if( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y-1, curr.z)) == piece.noBlockAt(Coordinates(curr.x, curr.y-1, curr.z+1)) ) )
    {
        const int rowOfBackLeftEdge = myDepth-curr.z+curr.x+curr.y-1;
        const int charIndexOfBackLeftEdge = ((myWidth-1)*2)+1-((curr.x-curr.y)*2);
        (*drawArea[rowOfBackLeftEdge])[charIndexOfBackLeftEdge] = '/';
    }
    if( piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z-1)) == piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z-1)) ) )
    {
        const int rowOfBottomleftEdge = myDepth-curr.z+curr.x+curr.y+1;
        const int charIndexOfBottomLeftEdge = ((myWidth-1)*2)+3-((curr.x-curr.y)*2);
        (*drawArea[rowOfBottomleftEdge])[charIndexOfBottomLeftEdge] = '/';
    }
}

void CanvasPrinter::drawYAxisLines(PrintablePiece piece, const Coordinates curr, QVector<QString*> drawArea)
{
    if( piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z+1)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) == piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z)) ) )
    {
        const int rowOfTopLeftEdge = myDepth-curr.z+curr.x+curr.y;
        const int charIndexOfTopLeftEdge = ((myWidth-1)*2)+1-((curr.x-curr.y)*2);
        (*drawArea[rowOfTopLeftEdge])[charIndexOfTopLeftEdge] = '\\';
    }
    if( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) &&
        ( piece.noBlockAt(Coordinates(curr.x-1, curr.y, curr.z)) == piece.noBlockAt(Coordinates(curr.x-1, curr.y, curr.z+1)) ) )
    {
        const int rowOfBackRightEdge = myDepth-curr.z+curr.x+curr.y-1;
        const int charIndexOfBackRightEdge = ((myWidth-1)*2)+3-((curr.x-curr.y)*2);
        (*drawArea[rowOfBackRightEdge])[charIndexOfBackRightEdge] = '\\';
    }
    if( piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z-1)) == piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z-1)) ) )
    {
        const int rowOfBottomleftEdge = myDepth-curr.z+curr.x+curr.y+1;
        const int charIndexOfBottomLeftEdge = ((myWidth-1)*2)+1-((curr.x-curr.y)*2);
        (*drawArea[rowOfBottomleftEdge])[charIndexOfBottomLeftEdge] = '\\';
    }
}

void CanvasPrinter::drawZAxisLines(PrintablePiece piece, const Coordinates curr, QVector<QString*> drawArea)
{
    if( piece.noBlockAt(Coordinates(curr.x+1, curr.y+1, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z)) == piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z)) ) )
    {
        const int rowOfBlockFront = myDepth-curr.z+curr.x+curr.y+1;
        const int charIndexOfBlockFront = ((myWidth-1)*2)+2-((curr.x-curr.y)*2);
        (*drawArea[rowOfBlockFront])[charIndexOfBlockFront] = '|';
    }
    if( piece.noBlockAt(Coordinates(curr.x+1, curr.y, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x, curr.y-1, curr.z)) || (!piece.noBlockAt(Coordinates(curr.x+1, curr.y-1, curr.z))) ) )
    {
        const int rowOfBlockLeft = myDepth-curr.z+curr.x+curr.y;
        const int charIndexOfBlockLeft = ((myWidth-1)*2)-((curr.x-curr.y)*2);
        (*drawArea[rowOfBlockLeft])[charIndexOfBlockLeft] = '|';
    }
    if( piece.noBlockAt(Coordinates(curr.x, curr.y+1, curr.z)) &&
        ( piece.noBlockAt(Coordinates(curr.x-1, curr.y, curr.z)) || (!piece.noBlockAt(Coordinates(curr.x-1, curr.y+1, curr.z))) ) )
    {
        const int rowOfBlockRight = myDepth-curr.z+curr.x+curr.y;
        const int charIndexOfBlockRight = ((myWidth-1)*2)+4-((curr.x-curr.y)*2);
        (*drawArea[rowOfBlockRight])[charIndexOfBlockRight] = '|';
    }
}

void CanvasPrinter::drawBlockTop(PrintablePiece piece, const Coordinates curr, QVector<QString*> drawArea)
{
    if( piece.noBlockAt(Coordinates(curr.x, curr.y, curr.z+1)) )
    {
        const int charIndexOfBlockTop = ((myWidth-1)*2)+2-((curr.x-curr.y)*2);
        int rowOfBlockTop = myDepth-curr.z+curr.x+curr.y;
        (*drawArea[rowOfBlockTop])[charIndexOfBlockTop] = ' ';
        rowOfBlockTop = myDepth-curr.z+curr.x+curr.y-1;
        (*drawArea[rowOfBlockTop])[charIndexOfBlockTop] = ' ';
    }
}

QString CanvasPrinter::printPieceBlocksToCanvas(const QString canvas, const PieceLocationContainer *pieceToPrint)
{
    int rowsToDraw = myWidth + myHeight + myDepth;
    QVector<QString*> drawArea;
    for( int row = 0 ; row < rowsToDraw ; ++row )
    {
        drawArea.append(new QString(canvas.section('\n',row,row)));
    }

    PrintablePiece printablePiece(pieceToPrint);
    QVector<PrintableBlock> pieceBlocks = printablePiece.getBlockList();
    bool blocksLeftToPrint;
    Coordinates frontMost(myWidth,myHeight,myDepth);
    do
    {
        blocksLeftToPrint= false;
        const Coordinates *back = &frontMost;
        PrintableBlock* blockToPrint = Q_NULLPTR;
        QVector<PrintableBlock>::iterator i;
        for (i = pieceBlocks.begin() ; i != pieceBlocks.end() ; ++i )
        {
            if( i->notPrinted() )
            {
                blocksLeftToPrint = true;
                const Coordinates* curr = i->coords();
                if( (*back) > (*curr) )
                {
                    back = curr;
                    blockToPrint = i;
                }
            }
        }
        if( blockToPrint )
        {
            blockToPrint->setPrinted();
            drawXAxisLines(printablePiece, *back, drawArea);
            drawYAxisLines(printablePiece, *back, drawArea);
            drawZAxisLines(printablePiece, *back, drawArea);
            drawBlockTop(printablePiece, *back, drawArea);
        }
    } while( blocksLeftToPrint );
    return createCombinedStringForDrawing(&drawArea);
}
