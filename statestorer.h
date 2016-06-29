#ifndef STATESTORER_H
#define STATESTORER_H
#include <QString>
#include <QVector>

class StateStorer
{
    friend class SDNCubeSolverTest;
public:
    StateStorer(int num, QString name);
    void setXCoords(int *coordlist);
    void setYCoords(int *coordlist);
    void setZCoords(int *coordlist);
    void setRotations(int *rotationlist);
    void writeFile();
    int getNumItems();
    int getXCoord(int index);
    int getYCoord(int index);
    int getZCoord(int index);
    int getRotations(int index);
private:
    StateStorer();
    int numItems;
    QString filename;
    QVector<int> xCoords;
    QVector<int> yCoords;
    QVector<int> zCoords;
    QVector<int> rotations;
};

#endif // STATESTORER_H
