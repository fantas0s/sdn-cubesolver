#include <iostream>
#include "puzzlecontainer.h"
#include "piececreator.h"
#include <QDebug>
#include <stdint.h>
#include <QDateTime>
#include "statestorer.h"
#define NUM_PIECES 13

const int cubeDimension = 4;
const int maxRotations = 10;
int64_t progress = 0;
const int iterationsMax = cubeDimension*cubeDimension*cubeDimension*maxRotations;
#ifdef FULL_MODE
const int level0iterationsMax = iterationsMax;
#else
const int level0iterationsMax = 2;
#endif
static int xCoord[NUM_PIECES];
static int yCoord[NUM_PIECES];
static int zCoord[NUM_PIECES];
static int rotations[NUM_PIECES];
static PuzzlePiece allPieces[NUM_PIECES];
static Coordinates positions[NUM_PIECES];
static PieceLocationContainer containers[NUM_PIECES];
static QDateTime startTime;
static StateStorer *backup;

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

void makeBackup()
{
    backup->setRotations(rotations);
    backup->setXCoords(xCoord);
    backup->setYCoords(yCoord);
    backup->setZCoords(zCoord);
    backup->writeFile();
}

int countIterations(int index)
{
    return (rotations[index]*(cubeDimension*cubeDimension*cubeDimension))
            + (xCoord[index]*(cubeDimension*cubeDimension))
            + (yCoord[index]*cubeDimension)
            + zCoord[index]
            + 1;
}

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, const int readIndex);

bool addPiecesToCubeStartingFromIndex(PuzzleContainer *cube, const int readIndex)
{
    progress++;
    if( 0 == (progress & ((int64_t)0xffff)) )
    {
        const qint64 msecs = startTime.msecsTo(QDateTime::currentDateTime());
        const qint64 secs = msecs/1000;
        const int level0iterations = countIterations(0);
        const int level1iterations = countIterations(1);
        const int level2iterations = countIterations(2);
        std::cout << "Progressing " << progress << " (" << level0iterations << "/" << level0iterationsMax
                  << ") (" << level1iterations << "/" << iterationsMax
                  << ") (" << level2iterations << "/" << iterationsMax << ") (runtime " << secs << " seconds)\n";
        makeBackup();
    }
    Coordinates *currentPos = &(positions[readIndex]);
    for( ; rotations[readIndex] < maxRotations ; ++rotations[readIndex] )
    {
        for( ; xCoord[readIndex] < cubeDimension ; ++xCoord[readIndex] )
        {
            currentPos->x = xCoord[readIndex];
            for( ; yCoord[readIndex] < cubeDimension ; ++yCoord[readIndex] )
            {
                currentPos->y = yCoord[readIndex];
                for( ; zCoord[readIndex] < cubeDimension ; ++zCoord[readIndex] )
                {
                    currentPos->z = zCoord[readIndex];
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
                    } // if(cube.add())
                    // did not fit, try again
                } // for z
                zCoord[readIndex] = 0;
            } // for y
            yCoord[readIndex] = 0;
        } // for x
        xCoord[readIndex] = 0;
        allPieces[readIndex].rotate();
    } // for rotate
    rotations[readIndex] = 0;
    // We could not fit this piece (or adjacent pieces) to any place in any rotation.
    return false;
}

bool addLevel0PieceToCubeAndContinue(PuzzleContainer *cube)
{
    Coordinates *currentPos = &(positions[0]);
#ifdef FULL_MODE
    for( ; rotations[0] < maxRotations ; ++rotations[0] )
    {
        for( ; xCoord[0] < cubeDimension ; ++xCoord[0] )
        {
            currentPos->x = xCoord[0];
            for( ; yCoord[0] < cubeDimension ; ++yCoord[0] )
            {
                currentPos->y = yCoord[0];
                for( ; zCoord[0] < cubeDimension ; ++zCoord[0] )
                {
                    currentPos->z = zCoord[0];
#else
                currentPos->x = 0;
                currentPos->y = 0;
                for( ; zCoord[0] < 2 ; ++zCoord[0] )
#endif
                {
                    currentPos->z = zCoord[0];
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
                    // did not fit, try again
                } // for z
#ifdef FULL_MODE
                zCoord[0] = 0;
            } // for y
            yCoord[0] = 0;
        } // for x
        xCoord[0] = 0;
        allPieces[0].rotate();
    } // for rotate
    rotations[0] = 0;
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
     * removed floating point operations from this file:       64 * 64 * 84       seconds = 4 days!
     * (only two positions of first piece are needed:          2 * 64 * 84        seconds = 3 hours)
     * after increasing rotations to 10 and changing order:    2 * 10 * 10482     seconds = 2 days 10 hours.
     */
    PuzzleContainer cube(cubeDimension,cubeDimension,cubeDimension);
    createAllPieces();
    StateStorer savedState(NUM_PIECES, QString("../sdn-cubesolver/savedstate.txt"));
    for( int index = 0 ; index < NUM_PIECES ; ++index )
    {
        containers[index] = PieceLocationContainer(&(allPieces[index]), &(positions[index]));
        xCoord[index] = savedState.getXCoord(index);
        yCoord[index] = savedState.getYCoord(index);
        zCoord[index] = savedState.getZCoord(index);
        rotations[index] = savedState.getRotations(index);
        for( int rotate = 0 ; rotate < rotations[index] ; ++rotate )
        {
            allPieces[index].rotate();
        }
    }
    backup = &savedState;
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
