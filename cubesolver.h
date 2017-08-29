#ifndef CUBESOLVER_H
#define CUBESOLVER_H
#include "puzzlecontainer.h"
#include "statestorer.h"
#include <QDateTime>
#include <QDir>

/* CONSTANTS */
#define NUM_PIECES 13

class CubeSolver {
public:
    CubeSolver();
    void runCubeSolveAlgorithm();
private:
    bool addLevel0PieceToCubeAndContinue();
    bool addPiecesToCubeStartingFromIndex(const int readIndex);
    int countIterations(int index) const;
    void createAllPieces();
    void makeBackup();
    void printSetupIfHighestSoFar(const int numOfPiecesInCube);
    PuzzleContainer* cube;
    int maxNumOfPiecesFittedSoFar;
    int xCoord[NUM_PIECES];
    int yCoord[NUM_PIECES];
    int zCoord[NUM_PIECES];
    int rotations[NUM_PIECES];
    PuzzlePiece allPieces[NUM_PIECES];
    Coordinates positions[NUM_PIECES];
    PieceLocationContainer containers[NUM_PIECES];
    QDateTime startTime;
    StateStorer *backup;
    QDir* savedStateDirectory;
};
#endif // CUBESOLVER_H
