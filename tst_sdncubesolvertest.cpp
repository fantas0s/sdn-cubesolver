#include <QString>
#include <QtTest>
#include "puzzlecontainer.h"
#include "puzzlepiece.h"
#include "canvasprinter.hpp"
#include <iostream>

class SDNCubeSolverTest : public QObject
{
    Q_OBJECT

public:
    SDNCubeSolverTest();

private Q_SLOTS:
    void createOneTimeOnePiece();
    void createTwoTimeOnePiece();
    void createInvalidPiece();
    void noBlockAt();
    void addOneTimeOnePiece();
    void addFiveTimeOnePiece();
    void renderToGrid();
    void addOverlappingOneTimeOnePieces();
    void popPiece();
    void printEmptyGrid();
    void printPieceBlocksToCanvas();
    void printPlusPiece();
    void printSteps();
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
    QVector<PieceBlock> blocksList = piece.getBlockList();
    QCOMPARE(blocksList.length(), 1);
    Coordinates coordinates = blocksList.at(0).coords();
    QCOMPARE(coordinates.x, 0);
    QCOMPARE(coordinates.y, 0);
    QCOMPARE(coordinates.z, 0);
}

void SDNCubeSolverTest::createTwoTimeOnePiece()
{
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,2,3));
    QCOMPARE(piece.numBlocks(), 2);
    QVector<PieceBlock> blocksList = piece.getBlockList();
    QCOMPARE(blocksList.length(), 2);
    Coordinates coordinates = blocksList.at(0).coords();
    QCOMPARE(coordinates.x, 0);
    QCOMPARE(coordinates.y, 0);
    QCOMPARE(coordinates.z, 0);
    coordinates = blocksList.at(1).coords();
    QCOMPARE(coordinates.x, 1);
    QCOMPARE(coordinates.y, 2);
    QCOMPARE(coordinates.z, 3);
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

void SDNCubeSolverTest::noBlockAt()
{
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    QCOMPARE(piece.noBlockAt(Coordinates(1,1,0)), true);
    QCOMPARE(piece.noBlockAt(Coordinates(0,1,0)), false);
}

void SDNCubeSolverTest::addOneTimeOnePiece()
{
    PuzzleContainer cube(1,1,1);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    Coordinates coords(0,0,0);
    QVERIFY(cube.add(PieceLocationContainer(piece, coords)));
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
    Coordinates coords(0,0,0);
    QCOMPARE(cube.add(PieceLocationContainer(piece, coords)), false);
}

void SDNCubeSolverTest::renderToGrid()
{
    PuzzleContainer cube(4,4,4);
    int grid[cube.myWidth][cube.myHeight][cube.myDepth];
    int* returned = cube.renderPiecesToGrid();
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
    Coordinates coords(0,0,0);
    cube.piecesInContainer.append(PieceLocationContainer(piece, coords));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,2,0));
    piece.addBlock(PieceBlock(0,3,0));
    cube.piecesInContainer.append(PieceLocationContainer(piece, coords));
    returned = cube.renderPiecesToGrid();
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
    Coordinates coords(0,0,0);
    QVERIFY(cube.add(PieceLocationContainer(piece, coords)));
    int grid[cube.myWidth][cube.myHeight][cube.myDepth];
    int* returned = cube.renderPiecesToGrid();
    memcpy(grid, returned, sizeof(grid));
    QCOMPARE(grid[0][0][0], 1);
    QCOMPARE(cube.add(PieceLocationContainer(piece, coords)), false);
    returned = cube.renderPiecesToGrid();
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
    Coordinates coords(0,0,0);
    QVERIFY(cube.add(PieceLocationContainer(piece, coords)));
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    coords = Coordinates(1,1,1);
    QVERIFY(cube.add(PieceLocationContainer(piece, coords)));
    int grid[cube.myWidth][cube.myHeight][cube.myDepth];
    int* returned = cube.renderPiecesToGrid();
    memcpy(grid, returned, sizeof(grid));
    QCOMPARE(grid[0][0][0], 1);
    QCOMPARE(grid[1][0][0], 1);
    QCOMPARE(grid[0][1][0], 1);
    QCOMPARE(grid[0][0][1], 1);
    QCOMPARE(grid[1][1][1], 1);
    cube.pop();
    returned = cube.renderPiecesToGrid();
    memcpy(grid, returned, sizeof(grid));
    QCOMPARE(grid[0][0][0], 1);
    QCOMPARE(grid[1][1][1], 0);
    cube.pop();
    QCOMPARE(cube.piecesInContainer.length(), 0);
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

void SDNCubeSolverTest::printPieceBlocksToCanvas()
{
    QString canvas = QString(
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
    CanvasPrinter printer(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,0,1));
    Coordinates coords(0,0,1);
    QString printedCanvas = printer.printPieceBlocksToCanvas(canvas, PieceLocationContainer(piece, coords));
    QCOMPARE(printedCanvas, expectedPieceBlocks);
}

void SDNCubeSolverTest::printPlusPiece()
{
    CanvasPrinter printer(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    piece.addBlock(PieceBlock(1,0,0));
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(-1,0,0));
    piece.addBlock(PieceBlock(0,-1,0));
    Coordinates coords(1,1,0);
    QString canvas = printer.printEmptyGrid();
    QString printedCanvas = printer.printPieceBlocksToCanvas(canvas, PieceLocationContainer(piece, coords));
    std::cout << printedCanvas.toStdString();
    QCOMPARE(printedCanvas, expectedPieceBlocks);
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
    Coordinates coords(0,0,0);
    cube.add(PieceLocationContainer(piece, coords));
    QString instructions = cube.printSteps();
    QString expected = expectedEmpty+"\n"+expectedFirstPiece;
    QCOMPARE(instructions, expected);
    piece = PuzzlePiece();
    piece.addBlock(PieceBlock(0,0,0));
    coords = Coordinates(1,1,1);
    cube.add(PieceLocationContainer(piece, coords));
    instructions = cube.printSteps();
    expected = expectedEmpty+"\n"+expectedFirstPiece+"\n"+expectedSecondPiece;
    QCOMPARE(instructions, expected);
}

QTEST_APPLESS_MAIN(SDNCubeSolverTest)

#include "tst_sdncubesolvertest.moc"
