#include <QString>
#include <QtTest>
#include "puzzlecontainer.h"
#include "puzzlepiece.h"
#include "canvasprinter.hpp"
#include <iostream>
#include "printableblock.h"
#include "printablepiece.h"
#include "piececreator.h"

class SDNCubeSolverTest : public QObject
{
    Q_OBJECT

public:
    SDNCubeSolverTest();

private Q_SLOTS:
    void createOneTimeOnePiece();
    void createTwoTimeOnePiece();
    void createInvalidPiece();
    void createContainer();
    void noBlockAt();
    void rotatePiece();
    void addOneTimeOnePiece();
    void addFiveTimeOnePiece();
    void renderToGrid();
    void addOverlappingOneTimeOnePieces();
    void popPiece();
    void createPrintablePiece();
    void printEmptyGrid();
    void printPieceBlocksToCanvas();
    void printPlusPiece();
    void printSteps();
    void addAllButOnePieceToCube();
};

SDNCubeSolverTest::SDNCubeSolverTest()
{
}

void SDNCubeSolverTest::createOneTimeOnePiece()
{
    PuzzlePiece piece;
    QCOMPARE(piece.numBlocks(), 0);
    piece.addBlock(PieceBlock(0,0,0));
    QCOMPARE(piece.numBlocks(), 1);
    const PieceBlock* blocksList = piece.getBlockList();
    const Coordinates *coordinates = blocksList[0].coords();
    QCOMPARE(coordinates->x, 0);
    QCOMPARE(coordinates->y, 0);
    QCOMPARE(coordinates->z, 0);
}

void SDNCubeSolverTest::createTwoTimeOnePiece()
{
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,2,3));
    QCOMPARE(piece.numBlocks(), 2);
    const PieceBlock* blocksList = piece.getBlockList();
    const Coordinates *coordinates = blocksList[0].coords();
    QCOMPARE(coordinates->x, 0);
    QCOMPARE(coordinates->y, 0);
    QCOMPARE(coordinates->z, 0);
    coordinates = blocksList[1].coords();
    QCOMPARE(coordinates->x, 1);
    QCOMPARE(coordinates->y, 2);
    QCOMPARE(coordinates->z, 3);
}

void SDNCubeSolverTest::createInvalidPiece()
{
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,0,1));
    QCOMPARE(piece.numBlocks(), 3);
    piece.addBlock(PieceBlock(0,1,0));
    QCOMPARE(piece.numBlocks(), 3);
}

void SDNCubeSolverTest::createContainer()
{
    PuzzlePiece piece1;
    piece1.addBlock(PieceBlock(1,2,3));
    Coordinates location1(4,5,6);
    PieceLocationContainer container1(&piece1, &location1);
    QCOMPARE(container1.location()->x, 4);
    QCOMPARE(container1.location()->y, 5);
    QCOMPARE(container1.location()->z, 6);
    QCOMPARE(container1.piece()->getBlockList()[0].coords()->x, 1);
    QCOMPARE(container1.piece()->getBlockList()[0].coords()->y, 2);
    QCOMPARE(container1.piece()->getBlockList()[0].coords()->z, 3);
}

void SDNCubeSolverTest::noBlockAt()
{
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    Coordinates location(1,1,1);
    PieceLocationContainer container(&piece, &location);
    PrintablePiece pPiece(&container);
    QCOMPARE(pPiece.noBlockAt(Coordinates(2,2,1)), true);
    QCOMPARE(pPiece.noBlockAt(Coordinates(1,2,1)), false);
}

void SDNCubeSolverTest::rotatePiece()
{
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,2,0));
    piece.addBlock(PieceBlock(0,0,1));
    piece.addBlock(PieceBlock(0,0,2));
    piece.addBlock(PieceBlock(0,0,3));
    //Z axis rotations
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,2,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,2)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,3)), true);
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,-1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(2,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,2)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,3)), true);
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(-1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,-1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,-2,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,2)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,3)), true);
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(-1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(-2,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,2)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,3)), true);
    //Y axis rotations
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(2,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(3,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,-1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,2,0)), true);
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(-1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,-1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,-2)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,-3)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,2,0)), true);
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(-1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(-2,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(-3,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,2,0)), true);
    //X axis rotations
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,2,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,3,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,-1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,-2)), true);
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,-1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,-2,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,-1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,-2)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,-3)), true);
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,-1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,-2,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,-3,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,2)), true);
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,2,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,2)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,3)), true);
    piece.rotate();
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,-1,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(1,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(2,0,0)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,1)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,2)), true);
    QCOMPARE(piece.blockFoundAt(Coordinates(0,0,3)), true);
}

void SDNCubeSolverTest::addOneTimeOnePiece()
{
    PuzzleContainer cube(1,1,1);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    Coordinates location(0,0,0);
    PieceLocationContainer container(&piece, &location);
    QVERIFY(cube.add(&container));
}

void SDNCubeSolverTest::addFiveTimeOnePiece()
{
    PuzzleContainer cube(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,2,0));
    piece.addBlock(PieceBlock(0,3,0));
    piece.addBlock(PieceBlock(0,4,0));
    Coordinates location(0,0,0);
    PieceLocationContainer container(&piece, &location);
    QCOMPARE(cube.add(&container), false);
}

void SDNCubeSolverTest::renderToGrid()
{
    PuzzleContainer cube(4,4,4);
    int grid[cube.myWidth][cube.myHeight][cube.myDepth];
    const int* returned = cube.getGrid();
    memcpy(grid, returned, sizeof(grid));
    QCOMPARE(grid[cube.myWidth-1][cube.myHeight-1][cube.myDepth-1], 0);
    QCOMPARE(grid[cube.myWidth-1][cube.myHeight-1][0], 0);
    QCOMPARE(grid[cube.myWidth-1][0][cube.myDepth-1], 0);
    QCOMPARE(grid[cube.myWidth-1][0][0], 0);
    QCOMPARE(grid[0][cube.myHeight-1][cube.myDepth-1], 0);
    QCOMPARE(grid[0][cube.myHeight-1][0], 0);
    QCOMPARE(grid[0][0][cube.myDepth-1], 0);
    QCOMPARE(grid[0][0][0], 0);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    Coordinates location(0,0,0);
    PieceLocationContainer container1(&piece, &location);
    PuzzlePiece piece2;
    piece2.addBlock(PieceBlock(0,0,0));
    piece2.addBlock(PieceBlock(0,1,0));
    piece2.addBlock(PieceBlock(0,2,0));
    piece2.addBlock(PieceBlock(0,3,0));
    PieceLocationContainer container2(&piece2, &location);
    cube.addToGrid(&container1);
    cube.addToGrid(&container2);
    returned = cube.getGrid();
    memcpy(grid, returned, sizeof(grid));
    QCOMPARE(grid[0][0][0], 2);
    QCOMPARE(grid[0][1][0], 1);
    QCOMPARE(grid[0][2][0], 1);
    QCOMPARE(grid[0][3][0], 1);
}

void SDNCubeSolverTest::addOverlappingOneTimeOnePieces()
{
    PuzzleContainer cube(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    Coordinates location(0,0,0);
    PieceLocationContainer container(&piece, &location);
    QVERIFY(cube.add(&container));
    int grid[cube.myWidth][cube.myHeight][cube.myDepth];
    const int* returned = cube.getGrid();
    memcpy(grid, returned, sizeof(grid));
    QCOMPARE(grid[0][0][0], 1);
    PuzzlePiece piece2;
    piece2.addBlock(PieceBlock(0,0,0));
    PieceLocationContainer container2(&piece2, &location);
    QCOMPARE(cube.add(&container2), false);
    returned = cube.getGrid();
    memcpy(grid, returned, sizeof(grid));
    QCOMPARE(grid[0][0][0], 1);
}

void SDNCubeSolverTest::popPiece()
{
    PuzzleContainer cube(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,0,1));
    Coordinates location(0,0,0);
    PieceLocationContainer container(&piece, &location);
    QVERIFY(cube.add(&container));
    PuzzlePiece piece2;
    piece2.addBlock(PieceBlock(0,0,0));
    Coordinates location2(1,1,1);
    PieceLocationContainer container2(&piece2, &location2);
    QVERIFY(cube.add(&container2));
    int grid[cube.myWidth][cube.myHeight][cube.myDepth];
    const int* returned = cube.getGrid();
    memcpy(grid, returned, sizeof(grid));
    QCOMPARE(grid[0][0][0], 1);
    QCOMPARE(grid[1][0][0], 1);
    QCOMPARE(grid[0][1][0], 1);
    QCOMPARE(grid[0][0][1], 1);
    QCOMPARE(grid[1][1][1], 1);
    cube.pop();
    returned = cube.getGrid();
    memcpy(grid, returned, sizeof(grid));
    QCOMPARE(grid[0][0][0], 1);
    QCOMPARE(grid[1][1][1], 0);
    cube.pop();
    QCOMPARE(cube.piecesInContainer.length(), 0);
}

void SDNCubeSolverTest::createPrintablePiece()
{
    PieceBlock block(1,2,3);
    PrintableBlock printableB(block);
    PieceBlock* parentClassObject = &printableB;
    QCOMPARE(printableB.coords()->x, 1);
    QCOMPARE(printableB.coords()->y, 2);
    QCOMPARE(printableB.coords()->z, 3);
    QCOMPARE(parentClassObject->coords()->x, 1);
    QCOMPARE(parentClassObject->coords()->y, 2);
    QCOMPARE(parentClassObject->coords()->z, 3);
    QCOMPARE(printableB.notPrinted(), true);
    printableB.setPrinted();
    QCOMPARE(printableB.notPrinted(), false);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(2,3,4));
    Coordinates location(0,0,0);
    PieceLocationContainer container(&piece, &location);
    PrintablePiece printableP(&container);
    QVector<PrintableBlock> blockV = printableP.getBlockList();
    QCOMPARE(blockV.length(), 1);
    QCOMPARE(blockV.at(0).coords()->y, 3);
}

static const QString expectedEmpty2x3x4 = QString(
"   /|\\     \n"
" /  |  \\   \n"
"|   |    \\ \n"
"|   |     |\n"
"|  / \\    |\n"
"|/     \\  |\n"
" \\       \\|\n"
"   \\     / \n"
"     \\ /   \n");
static const QString expectedEmpty4x3x2 = QString(
"       /|\\     \n"
"     /  |  \\   \n"
"   /   / \\   \\ \n"
" /   /     \\  |\n"
"|  /         \\|\n"
"|/           / \n"
" \\         /   \n"
"   \\     /     \n"
"     \\ /       \n");

void SDNCubeSolverTest::printEmptyGrid()
{
    CanvasPrinter printer(2,3,4);
    QString result = printer.printEmptyGrid();
    QCOMPARE(result, expectedEmpty2x3x4);
    printer = CanvasPrinter(4,3,2);
    result = printer.printEmptyGrid();
    QCOMPARE(result, expectedEmpty4x3x2);
}

static const QString expectedPieceBlocks = QString(
"                 \n"
"       / \\       \n"
"      |\\ /|      \n"
"      | |/ \\     \n"
"       \\ \\ /|    \n"
"         \\|/     \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n");

static const QString emptyCanvas = QString(
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n"
"                 \n");

void SDNCubeSolverTest::printPieceBlocksToCanvas()
{
    CanvasPrinter printer(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,0,1));
    Coordinates location(0,0,1);
    PieceLocationContainer container(&piece, &location);
    QString printedCanvas = printer.printPieceBlocksToCanvas(QString(emptyCanvas), &container);
    QCOMPARE(printedCanvas, expectedPieceBlocks);
}

static const QString expectedPlus = QString(
"       /|\\       \n"
"     /  |  \\     \n"
"   /    |    \\   \n"
" /      |      \\ \n"
"|    / \\ / \\    |\n"
"|   |\\     /|   |\n"
"|  / /     \\ \\  |\n"
"|/  |\\ /|\\ /|  \\|\n"
" \\   \\|/ \\|/   / \n"
"   \\         /   \n"
"     \\     /     \n"
"       \\ /       \n");

void SDNCubeSolverTest::printPlusPiece()
{
    CanvasPrinter printer(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(-1,0,0));
    piece.addBlock(PieceBlock(0,-1,0));
    Coordinates location(1,1,0);
    QString canvas = printer.printEmptyGrid();
    PieceLocationContainer container(&piece, &location);
    QString printedCanvas = printer.printPieceBlocksToCanvas(canvas, &container);
    QCOMPARE(printedCanvas, expectedPlus);
}

static const QString expectedEmpty = QString(
"       /|\\       \n"
"     /  |  \\     \n"
"   /    |    \\   \n"
" /      |      \\ \n"
"|      / \\      |\n"
"|    /     \\    |\n"
"|  /         \\  |\n"
"|/             \\|\n"
" \\             / \n"
"   \\         /   \n"
"     \\     /     \n"
"       \\ /       \n");

static const QString expectedFirstPiece = QString(
"       /|\\       \n"
"     /  |  \\     \n"
"   /   / \\   \\   \n"
" /    |\\ /|    \\ \n"
"|    / \\|/ \\    |\n"
"|   |\\ /|\\ /|   |\n"
"|  / \\|/ \\|/ \\  |\n"
"|/             \\|\n"
" \\             / \n"
"   \\         /   \n"
"     \\     /     \n"
"       \\ /       \n");

static const QString expectedSecondPiece = QString(
"       /|\\       \n"
"     /  |  \\     \n"
"   /    |    \\   \n"
" /      |      \\ \n"
"|      / \\      |\n"
"|    /|\\ /|\\    |\n"
"|  /   \\|/   \\  |\n"
"|/             \\|\n"
" \\             / \n"
"   \\         /   \n"
"     \\     /     \n"
"       \\ /       \n");

void SDNCubeSolverTest::printSteps()
{
    PuzzleContainer cube(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,0,1));
    Coordinates location(0,0,0);
    PieceLocationContainer container(&piece, &location);
    cube.add(&container);
    QString instructions = cube.printSteps();
    QString expected = expectedEmpty+"\n"+expectedFirstPiece;
    QCOMPARE(instructions, expected);
    PuzzlePiece piece2;
    piece2.addBlock(PieceBlock(0,0,0));
    Coordinates location2(1,1,1);
    PieceLocationContainer container2(&piece2, &location2);
    cube.add(&container2);
    instructions = cube.printSteps();
    expected = expectedEmpty+"\n"+expectedFirstPiece+"\n"+expectedSecondPiece;
    QCOMPARE(instructions, expected);
}

void SDNCubeSolverTest::addAllButOnePieceToCube()
{
    PuzzleContainer cube(4,4,4);
    PuzzlePiece pieces[12];
    Coordinates locations[12];
    PieceLocationContainer containers[12];
    for( int containerIndex = 0 ; containerIndex < 12 ; containerIndex++ )
    {
        containers[containerIndex] = PieceLocationContainer(&(pieces[containerIndex]), &(locations[containerIndex]));
    }
    int index = 0;
    PieceCreator::createPieceOrangePlus(&(pieces[index]));
    locations[index].x = 0;
    locations[index].y = 0;
    locations[index].z = 0;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceBlue3DTetris(&(pieces[index]));
    pieces[index].rotate();
    pieces[index].rotate();
    pieces[index].rotate();
    locations[index].x = 3;
    locations[index].y = 0;
    locations[index].z = 1;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceBlackClothHanger(&(pieces[index]));
    pieces[index].rotate();
    locations[index].x = 1;
    locations[index].y = 3;
    locations[index].z = 1;
    QVERIFY(cube.add(&(containers[index])));
    index++;
/*    PieceCreator::createPieceOrangeDoubleL(&(pieces[index]));
    pieces[index].rotate(); // can not turn to proper way
    locations[index].x = 3;
    locations[index].y = 3;
    locations[index].z = 3;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceOrangeJigsawUp1(&(pieces[index]));
    locations[index].x = 0;
    locations[index].y = 0;
    locations[index].z = 0;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceOrangeJigsawUp2(&(pieces[index]));
    locations[index].x = 0;
    locations[index].y = 0;
    locations[index].z = 0;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceBlackLeveledT(&(pieces[index]));
    locations[index].x = 0;
    locations[index].y = 0;
    locations[index].z = 0;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceBlackKnobUpT(&(pieces[index]));
    locations[index].x = 0;
    locations[index].y = 0;
    locations[index].z = 0;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceBlackZigZag(&(pieces[index]));
    locations[index].x = 0;
    locations[index].y = 0;
    locations[index].z = 0;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceBlue3DL(&(pieces[index]));
    locations[index].x = 0;
    locations[index].y = 0;
    locations[index].z = 0;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceBlueDoubleL(&(pieces[index]));
    locations[index].x = 0;
    locations[index].y = 0;
    locations[index].z = 0;
    QVERIFY(cube.add(&(containers[index])));
    index++;
    PieceCreator::createPieceBlueFlatZigZag(&(pieces[index]));
    locations[index].x = 0;
    locations[index].y = 0;
    locations[index].z = 0;
    QVERIFY(cube.add(&(containers[index])));
    index++;*/
}

QTEST_APPLESS_MAIN(SDNCubeSolverTest)

#include "tst_sdncubesolvertest.moc"
