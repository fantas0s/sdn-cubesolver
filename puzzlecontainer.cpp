#include "puzzlecontainer.h"
#include "canvasprinter.hpp"

PuzzleContainer::PuzzleContainer(int width, int height, int depth) :
    myWidth(width),
    myHeight(height),
    myDepth(depth)
{
}

int* PuzzleContainer::renderPiecesToGrid()
{
    int *returnValue = (int*)malloc(myWidth*myHeight*myDepth*sizeof(int));
    int grid[myWidth][myHeight][myDepth];
    for( int z = 0 ; z < myDepth ; z++ )
    {
        for( int y = 0 ; y < myHeight ; y++ )
        {
            for( int x = 0 ; x < myWidth ; x++ )
            {
                grid[x][y][z] = 0;
            }
        }
    }

    QVector<PieceLocationContainer>::iterator containerIterator;
    for( containerIterator = piecesInContainer.begin() ; containerIterator != piecesInContainer.end() ; ++containerIterator )
    {
        PuzzlePiece piece = (*containerIterator).piece();
        Coordinates location = (*containerIterator).location();
        QVector<PieceBlock> pieceBlocks = piece.getBlockList();
        QVector<PieceBlock>::iterator blockIterator;
        for (blockIterator = pieceBlocks.begin(); blockIterator != pieceBlocks.end(); ++blockIterator)
        {
            grid[(*blockIterator).coords().x + location.x]
                [(*blockIterator).coords().y + location.y]
                [(*blockIterator).coords().z + location.z] += 1;
        }
    }
    memcpy(returnValue, grid, sizeof(grid));
    return returnValue;
}

bool PuzzleContainer::add(PieceLocationContainer pieceAndLocation)
{
    PuzzlePiece piece = pieceAndLocation.piece();
    Coordinates location = pieceAndLocation.location();
    bool doesNotFit = false;
    QVector<PieceBlock> pieceBlocks = piece.getBlockList();
    QVector<PieceBlock>::iterator i;
    for (i = pieceBlocks.begin(); i != pieceBlocks.end(); ++i)
    {
        if( ((*i).coords().x + location.x < 0) ||
            ((*i).coords().x + location.x >= myWidth) ||
            ((*i).coords().y + location.y < 0) ||
            ((*i).coords().y + location.y >= myHeight) ||
            ((*i).coords().z + location.z < 0) ||
            ((*i).coords().z + location.z >= myDepth) )
        {
            doesNotFit = true;
            break;
        }
    }
    if( false == doesNotFit )
    {
        piecesInContainer.append(pieceAndLocation);
        int grid[myWidth][myHeight][myDepth];
        int* gridPtr = renderPiecesToGrid();
        memcpy(grid, gridPtr, sizeof(grid));
        for( int z = 0 ; z < myDepth ; z++ )
        {
            for( int y = 0 ; y < myHeight ; y++ )
            {
                for( int x = 0 ; x < myWidth ; x++ )
                {
                    if(grid[x][y][z] > 1)
                    {
                        doesNotFit = true;
                    }
                }
            }
        }
        if( doesNotFit )
        {
            piecesInContainer.removeLast();
        }
    }

    return !doesNotFit;
}

void PuzzleContainer::pop()
{
    piecesInContainer.removeLast();
}

QString PuzzleContainer::printSteps()
{
    CanvasPrinter printer(myWidth, myHeight, myDepth);
    const QString emptyGridString = printer.printEmptyGrid();
    QString returnString = QString(emptyGridString);

    QVector<PieceLocationContainer>::iterator containerIterator;
    for( containerIterator = piecesInContainer.begin() ; containerIterator != piecesInContainer.end() ; ++containerIterator )
    {
        returnString += "\n";
        returnString += printer.printPieceBlocksToCanvas(emptyGridString, *containerIterator);
    }

    return returnString;
}
