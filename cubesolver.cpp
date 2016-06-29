#include <iostream>
#include "puzzlecontainer.h"
#include "piececreator.h"
#include <QDebug>
#include <stdint.h>
#include <QDateTime>
#define NUM_PIECES 13

const int cubeDimension = 4;
const int maxRotations = 10;
int64_t progress = 0;
int level0iterations = 0;
int level1iterations = 0;
const int iterationsMax = cubeDimension*cubeDimension*cubeDimension*maxRotations;
#ifdef FULL_MODE
const int level0iterationsMax = iterationsMax;
#else
const int level0iterationsMax = 2;
#endif
static PuzzlePiece allPieces[NUM_PIECES];
static Coordinates positions[NUM_PIECES];
static PieceLocationContainer containers[NUM_PIECES];
static QDateTime startTime;

void createAllPieces()
{
    int index = 0;
    PieceCreator::createPieceOrangePlus(&(allPieces[index]));
    index++;
    PieceCreator::createPieceBlue3DTetris(&(allPieces[index]));
    index++;
    PieceCreator::createPieceBlackClothHanger(&(allPieces[index]));
    index++;
    PieceCreator::createPieceOrangeDoubleL(&(allPieces[index]));
    index++;
    PieceCreator::createPieceOrangeJigsawUp1(&(allPieces[index]));
    index++;
    PieceCreator::createPieceOrangeJigsawUp2(&(allPieces[index]));
    index++;
    PieceCreator::createPieceBlackLeveledT(&(allPieces[index]));
    index++;
    PieceCreator::createPieceBlackKnobUpT(&(allPieces[index]));
    index++;
    PieceCreator::createPieceBlackZigZag(&(allPieces[index]));
    index++;
    PieceCreator::createPieceBlue3DL(&(allPieces[index]));
    index++;
    PieceCreator::createPieceBlueDoubleL(&(allPieces[index]));
    index++;
    PieceCreator::createPieceBlueFlatZigZag(&(allPieces[index]));
    index++;
    PieceCreator::createPieceBlueLittleL(&(allPieces[index]));
    index++;
    Q_ASSERT(index == NUM_PIECES);
}

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, const int readIndex);

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, const int readIndex)
{
    progress++;
    if( readIndex==1 )
    {
        level1iterations = 0;
    }
    if( 0 == (progress & ((int64_t)0xffff)) )
    {
        qint64 msecs = startTime.msecsTo(QDateTime::currentDateTime());
        qint64 secs = msecs/1000;
        std::cout << "Progressing " << progress << " (" << level0iterations << "/" << level0iterationsMax
                  << ") (" << level1iterations << "/" << iterationsMax << ") (runtime " << secs << " seconds)\n";
    }
    Coordinates *currentPos = &(positions[readIndex]);
    for( int rotations = 0 ; rotations < maxRotations ; ++rotations )
    {
        for( int x = 0 ; x < cubeDimension ; ++x )
        {
            currentPos->x = x;
            for( int y = 0 ; y < cubeDimension ; ++y )
            {
                currentPos->y = y;
                for( int z = 0; z < cubeDimension ; ++z )
                {
                    currentPos->z = z;
                    if( readIndex==1 )
                    {
                        level1iterations++;
                    }
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
                }
            }
        }
        allPieces[readIndex].rotate();
    }
    // We could not fit this piece (or adjacent pieces) to any place in any position.
    return false;
}

bool addLevel0PieceToCubeAndContinue(PuzzleContainer *cube)
{
    Coordinates *currentPos = &(positions[0]);
#ifdef FULL_MODE
    for( int rotations = 0 ; rotations < 6 ; ++rotations )
    {
        for( int x = 0 ; x < cubeDimension ; ++x )
        {
            currentPos->x = x;
            for( int y = 0 ; y < cubeDimension ; ++y )
            {
                currentPos->y = y;
                for( int z = 0; z < cubeDimension ; ++z )
#else
                currentPos->x = 0;
                currentPos->y = 0;
                for( int z = 0 ; z < 2 ; ++z )
#endif
                {
                    currentPos->z = z;
                    level0iterations++;
                    if( cube->add(&(containers[0])) )
                    {
                        // This piece fits. Add more pieces to the cube.
                        if( addPiecesToCubeStartingFromIndex(cube, 1) )
                        {
                            return true;
                        }
                        else
                        {
                            // No solution from this setup. Take our piece out and try again.
                            cube->pop();
                        }
                    }
                }
#ifdef FULL_MODE
            }
        }
        // did not fit, try again
       allPieces[0].rotate();
    }
#endif
    // No solution found
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
     * using pointers instead of objects in this file:         90 * 90 * 90 * 16  seconds = 135 days...
     * removed floating point operations from this file:       64 * 64 * 84 seconds = 4 days!
     *
     * Also: only two positions of first piece are needed, which means proper time should be 2 * 64 * 84 seconds = 3 hours.
     */
    PuzzleContainer cube(cubeDimension,cubeDimension,cubeDimension);
    createAllPieces();
    for( int index = 0 ; index < NUM_PIECES ; ++index )
    {
        containers[index] = PieceLocationContainer(&(allPieces[index]), &(positions[index]));
    }
    startTime = QDateTime::currentDateTime();
    if( addLevel0PieceToCubeAndContinue(&cube) )
    {
        qDebug() << "printing Steps";
        std::cout << cube.printSteps().toStdString();
    }
    else
    {
        std::cout << "FAILED!\n";
    }
}
