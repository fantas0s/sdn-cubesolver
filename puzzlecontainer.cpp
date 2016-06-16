#include "puzzlecontainer.h"

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

QString PuzzleContainer::printEmptyGrid()
{
    int rowsToDraw = myWidth + myHeight + myDepth;
    QString* drawArea[rowsToDraw];
    for( int row = 0 ; row < rowsToDraw ; ++row )
    {
        drawArea[row] = new QString();
        while( drawArea[row]->length() < (((myWidth+myHeight)*2)+1) )
        {
            *drawArea[row] += " ";
        }
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
    QString returnString;
    for( int row = 0 ; row < rowsToDraw ; ++row )
    {
        returnString += *drawArea[row];
        returnString += QString("\n");
        delete drawArea[row];
    }
    return returnString;
}

QString PuzzleContainer::printSteps()
{
    int grid[myWidth][myHeight][myDepth];
    int* gridPtr = renderPiecesToGrid();
    memcpy(grid, gridPtr, sizeof(grid));
    QString returnString = printEmptyGrid();

    return returnString;
}
