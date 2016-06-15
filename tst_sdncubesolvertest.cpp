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
    void addOneTimeOnePiece();
};

SDNCubeSolverTest::SDNCubeSolverTest()
{
}


void SDNCubeSolverTest::createOneTimeOnePiece()
{
    PuzzlePiece piece;
    PieceBlock block(0,0,0);
    QCOMPARE(piece.numBlocks(), 0);
    piece.addBlock(&block);
    QCOMPARE(piece.numBlocks(), 1);
    QVector<PieceBlock*> blocksList = piece.getBlockList();
    QCOMPARE(blocksList.length(), 1);
    QVector<int> coordinates = blocksList.at(0)->coords();
}

void SDNCubeSolverTest::addOneTimeOnePiece()
{
    PuzzleContainer cube;

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SDNCubeSolverTest)

#include "tst_sdncubesolvertest.moc"
