#include <iostream>
#include "puzzlecontainer.h"
#include <QDebug>

const int cubeDimension = 4;

QVector<PuzzlePiece> createAllPieces()
{
    QVector<PuzzlePiece> container;
    //orange Plus
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(-1,0,0));
    piece.addBlock(PieceBlock(0,-1,0));
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
    return container;
}

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, QVector<PuzzlePiece> pieces, const int readIndex);

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, QVector<PuzzlePiece> pieces, const int readIndex)
{
    PuzzlePiece* piece = const_cast<PuzzlePiece*>(&pieces.at(readIndex));
    for( int x = 0 ; x < cubeDimension ; ++x )
    {
        for( int y = 0 ; y < cubeDimension ; ++y )
        {
            for( int z = 0; z < cubeDimension ; ++z )
            {
                for( int rotations = 0 ; rotations < 6 ; ++rotations )
                {
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
    PuzzleContainer cube(cubeDimension,cubeDimension,cubeDimension);
    QVector<PuzzlePiece> pieces = createAllPieces();
    if( addPiecesToCubeStartingFromIndex(&cube, pieces, 0) )
    {
        std::cout << cube.printSteps().toStdString();
    }
    else
    {
        std::cout << "FAILED!\n";
    }
}
