#include <iostream>
#include "puzzlecontainer.h"
#include <QDebug>
#include <stdint.h>
#define NUM_PIECES 13

const int cubeDimension = 4;
const float maxPositions = cubeDimension*cubeDimension*cubeDimension*6;
int64_t progress = 0;
static PuzzlePiece allPieces[NUM_PIECES];
static Coordinates positions[NUM_PIECES];
static PieceLocationContainer containers[NUM_PIECES];

void createAllPieces()
{
    int index = 0;
    //orange Plus
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(1,2,0));
    allPieces[index] = piece;
    index++;
    //orange double-L
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(0,0,2));
    allPieces[index] = piece;
    index++;
    //orange jigsaw with up-part at end
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(2,1,1));
    allPieces[index] = piece;
    index++;
    //orange jigsaw with up-part before the end
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    allPieces[index] = piece;
    index++;
    // black cloth hanger
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    allPieces[index] = piece;
    index++;
    // black T-like with end knob in level with rest of it
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,-1,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    allPieces[index] = piece;
    index++;
    // black T-like with end knob up
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    allPieces[index] = piece;
    index++;
    // black zigzag
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    piece.addBlock(PieceBlock(2,1,1));
    allPieces[index] = piece;
    index++;
    // blue 3D'ish L
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,1,1));
    allPieces[index] = piece;
    index++;
    // blue double-L
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(2,1,0));
    allPieces[index] = piece;
    index++;
    // blue flat zigzag
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(2,2,0));
    allPieces[index] = piece;
    index++;
    // blue 3D tetris piece
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,0,1));
    allPieces[index] = piece;
    index++;
    // blue little L
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    allPieces[index] = piece;
    index++;
    Q_ASSERT(index == NUM_PIECES);
}

static int progressTable[NUM_PIECES] = {0};

int createTenPercentProgressValue(int x, int y, int z, int rotations)
{
    float current = (x*cubeDimension*cubeDimension*6)+(y*cubeDimension*6)+(z*6)+rotations;
    float tenPercentage = ((current * 10)-1) / maxPositions;
    return (int)tenPercentage;
}

void printProgress()
{
    std::cout << "Progress at ";
    for( int index = 0 ; index < NUM_PIECES ; index++ )
    {
        std::cout << progressTable[index];
    }
    std::cout << "/9999999999999\n";
}

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, const int readIndex);

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, const int readIndex)
{
    progress++;
    if( 0 == (progress & 0x00000fff) )
    {
        printProgress();
    }
    Coordinates *currentPos = &(positions[readIndex]);
    for( int x = 0 ; x < cubeDimension ; ++x )
    {
        currentPos->x = x;
        for( int y = 0 ; y < cubeDimension ; ++y )
        {
            currentPos->y = y;
            for( int z = 0; z < cubeDimension ; ++z )
            {
                currentPos->z = z;
                for( int rotations = 0 ; rotations < 6 ; ++rotations )
                {
                    progressTable[readIndex] = createTenPercentProgressValue(x, y, z, rotations);
                    if( cube->add(&(containers[readIndex])) )
                    {
                        // This piece fits. Was it the last one?
                        if( (readIndex+1) >= NUM_PIECES )
                        {
                            // YES! We're done!
                            qDebug() << "All" << readIndex+1 << "pieces added!";
                            return true;
                        }
                        else
                        {
                            // No, there are more pieces to place to the cube.
                            if( addPiecesToCubeStartingFromIndex(cube, readIndex+1) )
                            {
                                return true;
                            }
                            else
                            {
                                // No solution from this setup. Take last piece out and try again.
                                cube->pop();
                            }
                        }
                    }
                    // did not fit, try again
                   allPieces[readIndex].rotate();
                }
            }
        }
    }
    // We could not fit this piece (or adjacent pieces) to any place in any position.
    return false;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    /* Approximate time to try ALL combinations:
     * Unoptimized code:                                       90 * 90 * 90 * 400 seconds = 3375 days...
     * Use of vectors removed from class PuzzlePiece:          90 * 90 * 90 * 100 seconds = 843 days...
     * Added passing of const pointers instead of objects:     90 * 90 * 90 * 64  seconds = 540 days...
     * Use of QVector removed from this file:                  90 * 90 * 90 * 64  seconds = 540 days...
     * No more dynamic allocs in grid handling:                90 * 90 * 90 * 24  seconds = 202 days...
     * using pointers instead of objects in container vector:  90 * 90 * 90 * 24  seconds = 202 days...
     */
    PuzzleContainer cube(cubeDimension,cubeDimension,cubeDimension);
    createAllPieces();
    for( int index = 0 ; index < NUM_PIECES ; ++index )
    {
        containers[index] = PieceLocationContainer(&(allPieces[index]), &(positions[index]));
    }
    if( addPiecesToCubeStartingFromIndex(&cube, 0) )
    {
        qDebug() << "printing Steps";
        std::cout << cube.printSteps().toStdString();
    }
    else
    {
        std::cout << "FAILED!\n";
    }
}
