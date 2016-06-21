#include <iostream>
#include "puzzlecontainer.h"
#include <QDebug>
#include <stdint.h>
#define NUM_PIECES 13

const int cubeDimension = 4;
const float maxPositions = cubeDimension*cubeDimension*cubeDimension*6;
int64_t progress = 0;

QVector<PuzzlePiece> createAllPieces()
{
    QVector<PuzzlePiece> container;
    //orange Plus
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(1,2,0));
    container.append(piece);
    //orange double-L
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(0,0,2));
    container.append(piece);
    //orange jigsaw with up-part at end
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(2,1,1));
    container.append(piece);
    //orange jigsaw with up-part before the end
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    container.append(piece);
    // black cloth hanger
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    container.append(piece);
    // black T-like with end knob in level with rest of it
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,-1,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    container.append(piece);
    // black T-like with end knob up
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    container.append(piece);
    // black zigzag
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    piece.addBlock(PieceBlock(2,1,1));
    container.append(piece);
    // blue 3D'ish L
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,1,1));
    container.append(piece);
    // blue double-L
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(2,1,0));
    container.append(piece);
    // blue flat zigzag
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(2,1,0));
    piece.addBlock(PieceBlock(2,2,0));
    container.append(piece);
    // blue 3D tetris piece
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(2,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,0,1));
    container.append(piece);
    // blue little L
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(1,1,0));
    piece.addBlock(PieceBlock(1,1,1));
    container.append(piece);
    return container;
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

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, QVector<PuzzlePiece> pieces, const int readIndex);

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, QVector<PuzzlePiece> pieces, const int readIndex)
{
    progress++;
    if( 0 == (progress & 0x00000fff) )
    {
        printProgress();
    }
    PuzzlePiece* piece = const_cast<PuzzlePiece*>(&pieces.at(readIndex));
    for( int x = 0 ; x < cubeDimension ; ++x )
    {
        for( int y = 0 ; y < cubeDimension ; ++y )
        {
            for( int z = 0; z < cubeDimension ; ++z )
            {
                for( int rotations = 0 ; rotations < 6 ; ++rotations )
                {
                    progressTable[readIndex] = createTenPercentProgressValue(x, y, z, rotations);
                    if( cube->add(PieceLocationContainer(*piece, Coordinates(x,y,z))) )
                    {
                        // This piece fits. Are we done?
                        if( readIndex >= (pieces.length()-1) )
                        {
                            // YES! We're done!
                            qDebug() << "All" << readIndex+1 << "pieces added!";
                            return true;
                        }
                        else
                        {
                            // No, there are more pieces to place to the cube.
                            if( addPiecesToCubeStartingFromIndex(cube, pieces, readIndex+1) )
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
                    piece->rotate();
                }
            }
        }
    }
    // We could not fit this piece (or adjacent pieces) to any place in any position.
    return false;
}

int main(int argc, char *argv[])
{
    // Approximate time to try ALL combinations: 90 * 90 * 90 * 400 seconds = 3375 days...
    PuzzleContainer cube(cubeDimension,cubeDimension,cubeDimension);
    QVector<PuzzlePiece> pieces = createAllPieces();
    Q_ASSERT( pieces.length() == NUM_PIECES );
    if( addPiecesToCubeStartingFromIndex(&cube, pieces, 0) )
    {
        std::cout << cube.printSteps().toStdString();
    }
    else
    {
        std::cout << "FAILED!\n";
    }
}
