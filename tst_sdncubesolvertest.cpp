#include <QString>
#include <QtTest>
#include "puzzlecontainer.h"
#include "puzzlepiece.h"

class SDNCubeSolverTest : public QObject
{
    Q_OBJECT

public:
    SDNCubeSolverTest();

private Q_SLOTS:
    void createOneTimeOnePiece();
    void createTwoTimeOnePiece();
    void createInvalidPiece();
    void addOneTimeOnePiece();
    void addFiveTimeOnePiece();
    void renderToGrid();
    void addOverlappingOneTimeOnePieces();
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

void SDNCubeSolverTest::addOneTimeOnePiece()
{
    PuzzleContainer cube(1,1,1);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    Coordinates coords(0,0,0);
    QVERIFY(cube.add(piece, coords));
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
    QCOMPARE(cube.add(piece, coords), false);
}

void SDNCubeSolverTest::renderToGrid()
{
    PuzzleContainer cube(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    cube.pieces.append(piece);
    piece.addBlock(PieceBlock(0,1,0));
    piece.addBlock(PieceBlock(0,2,0));
    piece.addBlock(PieceBlock(0,3,0));
    Coordinates coords(0,0,0);
    cube.pieces.append(piece);
    cube.renderPiecesToGrid();
}

void SDNCubeSolverTest::addOverlappingOneTimeOnePieces()
{
    PuzzleContainer cube(4,4,4);
    PuzzlePiece piece;
    piece.addBlock(PieceBlock(0,0,0));
    Coordinates coords(0,0,0);
    QVERIFY(cube.add(piece, coords));
//    QCOMPARE(cube.add(piece, coords), false);
}

QTEST_APPLESS_MAIN(SDNCubeSolverTest)

#include "tst_sdncubesolvertest.moc"
