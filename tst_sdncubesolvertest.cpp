#include <QString>
#include <QtTest>
#include "puzzlecontainer.h"
#include "puzzlepiece.h"
#include "canvasprinter.hpp"
#include <iostream>
#include "printableblock.h"
#include "printablepiece.h"
#include "piececreator.h"
#include "statestorer.h"

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
    void stateStorerWrite();
    void stateStorerRead();
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

void SDNCubeSolverTest::stateStorerWrite()
{
    const int numItems = 8;
    int xCoord[numItems] = {0};
    int yCoord[numItems] = {0};
    int zCoord[numItems] = {0};
    int rotations[numItems] = {0};
    QFile emptyFile("testout.txt");
    QVERIFY(emptyFile.open(QIODevice::WriteOnly | QIODevice::Text));
    QTextStream out(&emptyFile);
    out << "";
    emptyFile.close();
    StateStorer storer(numItems, QString("testout.txt"));
    QCOMPARE(storer.numItems, numItems);
    QCOMPARE(storer.filename, QString("testout.txt"));
    QCOMPARE(storer.xCoords.length(), numItems);
    QCOMPARE(storer.yCoords.length(), numItems);
    QCOMPARE(storer.zCoords.length(), numItems);
    QCOMPARE(storer.rotations.length(), numItems);
    for( int i = 0 ; i < numItems ; ++i )
    {
        QCOMPARE(storer.xCoords.at(i), 0);
        QCOMPARE(storer.yCoords.at(i), 0);
        QCOMPARE(storer.zCoords.at(i), 0);
        QCOMPARE(storer.rotations.at(i), 0);
    }
    for( int i = 0 ; i < numItems ; ++i )
    {
        xCoord[i] = 1+i;
        yCoord[i] = numItems + i + 1;
        zCoord[i] = (numItems*2) + i + 1;
        rotations[i] = (numItems*3) + i + 1;
    }
    storer.setXCoords(xCoord);
    storer.setYCoords(yCoord);
    storer.setZCoords(zCoord);
    storer.setRotations(rotations);
    for( int i = 0 ; i < numItems ; ++i )
    {
        QCOMPARE(storer.xCoords.at(i), xCoord[i]);
        QCOMPARE(storer.yCoords.at(i), yCoord[i]);
        QCOMPARE(storer.zCoords.at(i), zCoord[i]);
        QCOMPARE(storer.rotations.at(i), rotations[i]);
    }
    storer.writeFile();
    QFile verificationFile("testout.txt");
    QVERIFY(verificationFile.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream input(&verificationFile);
    QVERIFY(!input.atEnd());
    QString header = input.readLine();
    QCOMPARE(header, QString("Number of items:"));
    QVERIFY(!input.atEnd());
    QString numberStr = input.readLine();
    QCOMPARE(numberStr.toInt(), numItems);
    QVERIFY(!input.atEnd());
    header = input.readLine();
    QCOMPARE(header, QString("X Coordinates:"));
    for( int i = 0 ; i < numItems ; ++i )
    {
        QVERIFY(!input.atEnd());
        numberStr = input.readLine();
        QCOMPARE(numberStr.toInt(), xCoord[i]);
    }
    QVERIFY(!input.atEnd());
    header = input.readLine();
    QCOMPARE(header, QString("Y Coordinates:"));
    for( int i = 0 ; i < numItems ; ++i )
    {
        QVERIFY(!input.atEnd());
        numberStr = input.readLine();
        QCOMPARE(numberStr.toInt(), yCoord[i]);
    }
    QVERIFY(!input.atEnd());
    header = input.readLine();
    QCOMPARE(header, QString("Z Coordinates:"));
    for( int i = 0 ; i < numItems ; ++i )
    {
        QVERIFY(!input.atEnd());
        numberStr = input.readLine();
        QCOMPARE(numberStr.toInt(), zCoord[i]);
    }
    QVERIFY(!input.atEnd());
    header = input.readLine();
    QCOMPARE(header, QString("Rotations:"));
    for( int i = 0 ; i < numItems ; ++i )
    {
        QVERIFY(!input.atEnd());
        numberStr = input.readLine();
        QCOMPARE(numberStr.toInt(), rotations[i]);
    }
    QVERIFY(input.atEnd());
    verificationFile.close();
}

void SDNCubeSolverTest::stateStorerRead()
{
    const int numItems = 4;
    QFile sourceFile("testin.txt");
    QVERIFY(sourceFile.open(QIODevice::WriteOnly | QIODevice::Text));
    QTextStream out(&sourceFile);
    out << QString("Number of items:\n");
    out << QString::number(numItems) << "\n";
    out << QString("X Coordinates:\n");
    for( int i = 0 ; i < numItems ; ++i )
    {
        out << QString::number(i+1) << "\n";
    }
    out << QString("Y Coordinates:\n");
    for( int i = 0 ; i < numItems ; ++i )
    {
        out << QString::number(10*(i+1)) << "\n";
    }
    out << QString("Z Coordinates:\n");
    for( int i = 0 ; i < numItems ; ++i )
    {
        out << QString::number(20*(i+1)) << "\n";
    }
    out << QString("Rotations:\n");
    for( int i = 0 ; i < numItems ; ++i )
    {
        out << QString::number(30*(i+1)) << "\n";
    }
    sourceFile.close();
    StateStorer storer(numItems, QString("testin.txt"));
    QCOMPARE(storer.numItems, numItems);
    QCOMPARE(storer.getNumItems(), numItems);
    QCOMPARE(storer.xCoords.length(), numItems);
    QCOMPARE(storer.yCoords.length(), numItems);
    QCOMPARE(storer.zCoords.length(), numItems);
    QCOMPARE(storer.rotations.length(), numItems);
    for( int i = 0 ; i < numItems ; ++i )
    {
        QCOMPARE(storer.xCoords.at(i), i+1);
        QCOMPARE(storer.getXCoord(i), i+1);
        QCOMPARE(storer.yCoords.at(i), 10*(i+1));
        QCOMPARE(storer.getYCoord(i), 10*(i+1));
        QCOMPARE(storer.zCoords.at(i), 20*(i+1));
        QCOMPARE(storer.getZCoord(i), 20*(i+1));
        QCOMPARE(storer.rotations.at(i), 30*(i+1));
        QCOMPARE(storer.getRotations(i), 30*(i+1));
    }
}

QTEST_APPLESS_MAIN(SDNCubeSolverTest)

#include "tst_sdncubesolvertest.moc"
