#include "puzzlecontainer.h"
#include "canvasprinter.hpp"

#define INDEX_IN_GRID(x,y,z)   (((z)*myDepth*myHeight)+((y)*myHeight)+(x))

PuzzleContainer::PuzzleContainer(int width, int height, int depth) :
    myWidth(width),
    myHeight(height),
    myDepth(depth),
    gridLength(width*height*depth)
{
    int sizeOfGrid = width*height*depth*sizeof(int);
    grid = (int*)malloc(sizeOfGrid);
    memset(grid, 0, sizeOfGrid);
}

const int* PuzzleContainer::getGrid()
{
    return grid;
}

void PuzzleContainer::addToGrid(const PieceLocationContainer *pieceAndLocation)
{
    const PuzzlePiece *piece = pieceAndLocation->piece();
    const Coordinates *location = pieceAndLocation->location();
    const PieceBlock *pieceBlocks = piece->getBlockList();
    for (int i = 0 ; i < piece->numBlocks() ; ++i )
    {
        const Coordinates *curr = pieceBlocks[i].coords();
        grid[INDEX_IN_GRID(curr->x + location->x, curr->y + location->y, curr->z + location->z)] += 1;
    }
}

void PuzzleContainer::removeFromGrid(const PieceLocationContainer *pieceAndLocation)
{
    const PuzzlePiece *piece = pieceAndLocation->piece();
    const Coordinates *location = pieceAndLocation->location();
    const PieceBlock *pieceBlocks = piece->getBlockList();
    for (int i = 0 ; i < piece->numBlocks() ; ++i )
    {
        const Coordinates *curr = pieceBlocks[i].coords();
        grid[INDEX_IN_GRID(curr->x + location->x, curr->y + location->y, curr->z + location->z)] -= 1;
    }
}

bool PuzzleContainer::gridHasOverlaps()
{
    for( int index = 0 ; index < gridLength ; ++index )
    {
        if( grid[index] > 1 )
            return true;
    }
    return false;
}

bool PuzzleContainer::add(const PieceLocationContainer *pieceAndLocation)
{
    const PuzzlePiece *piece = pieceAndLocation->piece();
    const Coordinates *location = pieceAndLocation->location();
    bool doesNotFit = false;
    const PieceBlock *pieceBlocks = piece->getBlockList();
    for (int i = 0 ; i < piece->numBlocks() ; ++i )
    {
        const Coordinates *curr = pieceBlocks[i].coords();
        if( (curr->x + location->x < 0) ||
            (curr->x + location->x >= myWidth) ||
            (curr->y + location->y < 0) ||
            (curr->y + location->y >= myHeight) ||
            (curr->z + location->z < 0) ||
            (curr->z + location->z >= myDepth) )
        {
            doesNotFit = true;
            break;
        }
    }
    if( false == doesNotFit )
    {
        addToGrid(pieceAndLocation);
        doesNotFit = gridHasOverlaps();
        if( doesNotFit )
        {
            removeFromGrid(pieceAndLocation);
        }
        else
        {
            piecesInContainer.append(pieceAndLocation);
        }
    }

    return !doesNotFit;
}

void PuzzleContainer::pop()
{
    removeFromGrid(piecesInContainer.last());
    piecesInContainer.removeLast();
}

QString PuzzleContainer::printSteps()
{
    CanvasPrinter printer(myWidth, myHeight, myDepth);
    const QString emptyGridString = printer.printEmptyGrid();
    QString returnString = QString(emptyGridString);

    QVector<const PieceLocationContainer*>::iterator containerIterator;
    for( containerIterator = piecesInContainer.begin() ; containerIterator != piecesInContainer.end() ; ++containerIterator )
    {
        returnString += "\n";
        returnString += printer.printPieceBlocksToCanvas(emptyGridString, *containerIterator);
    }

    return returnString;
}
