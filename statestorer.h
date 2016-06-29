#ifndef STATESTORER_H
#define STATESTORER_H
#include <QString>
#include <QVector>

class StateStorer
{
    friend class SDNCubeSolverTest;
public:
    StateStorer(int num, QString name);
    void setProgress(int64_t current);
    void setXCoords(int *coordlist);
    void setYCoords(int *coordlist);
    void setZCoords(int *coordlist);
    void setRotations(int *rotationlist);
    void writeFile();
private:
    StateStorer();
    int numItems;
    QString filename;
    int64_t progress;
    QVector<int> xCoords;
    QVector<int> yCoords;
    QVector<int> zCoords;
    QVector<int> rotations;
};

#endif // STATESTORER_H
