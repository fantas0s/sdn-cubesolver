#include "statestorer.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

StateStorer::StateStorer(int num, QString name) :
    numItems(num),
    filename(name),
    progress(0)
{
    QFile sourceFile(filename);
    bool wasNotLoadedFromFile = true;
    if(sourceFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream input(&sourceFile);
        if(!input.atEnd())
        {
            // Not empty
            QString header = input.readLine();
            QString numberStr = input.readLine();
            progress = numberStr.toInt();
            header = input.readLine();
            numberStr = input.readLine();
            if( numberStr.toInt() == num )
            {
                header = input.readLine();
                if(!input.atEnd())
                {
                    for( int i = 0 ; i < numItems ; ++i )
                    {
                        numberStr = input.readLine();
                        xCoords.append(numberStr.toInt());
                    }
                }
                header = input.readLine();
                if(!input.atEnd())
                {
                    for( int i = 0 ; i < numItems ; ++i )
                    {
                        numberStr = input.readLine();
                        yCoords.append(numberStr.toInt());
                    }
                }
                header = input.readLine();
                if(!input.atEnd())
                {
                    for( int i = 0 ; i < numItems ; ++i )
                    {
                        numberStr = input.readLine();
                        zCoords.append(numberStr.toInt());
                    }
                }
                header = input.readLine();
                if(!input.atEnd())
                {
                    for( int i = 0 ; i < (numItems-1) ; ++i )
                    {
                        numberStr = input.readLine();
                        rotations.append(numberStr.toInt());
                    }
                    if(!input.atEnd())
                    {
                        numberStr = input.readLine();
                        rotations.append(numberStr.toInt());
                        wasNotLoadedFromFile = false;
                    }
                }
            }
            if( wasNotLoadedFromFile )
            {
                qDebug() << "Loading from file" << filename << "failed, invalid content.";
                xCoords.clear();
                yCoords.clear();
                zCoords.clear();
                rotations.clear();
            }
        }
    }
    if( wasNotLoadedFromFile )
    {
        for( int i = 0 ; i < numItems ; ++i )
        {
            xCoords.append(0);
            yCoords.append(0);
            zCoords.append(0);
            rotations.append(0);
        }
    }
}

void StateStorer::setProgress(int64_t current)
{
    progress = current;
}

void StateStorer::setXCoords(int *coordlist)
{
    for( int i = 0 ; i < numItems ; ++i )
    {
        xCoords.replace(i, coordlist[i]);
    }
}

void StateStorer::setYCoords(int *coordlist)
{
    for( int i = 0 ; i < numItems ; ++i )
    {
        yCoords.replace(i, coordlist[i]);
    }
}

void StateStorer::setZCoords(int *coordlist)
{
    for( int i = 0 ; i < numItems ; ++i )
    {
        zCoords.replace(i, coordlist[i]);
    }
}

void StateStorer::setRotations(int *rotationlist)
{
    for( int i = 0 ; i < numItems ; ++i )
    {
        rotations.replace(i, rotationlist[i]);
    }
}

void StateStorer::writeFile()
{
    QFile outputFile(filename);
    if(!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "failed to open" << filename;
        return;
    }
    QTextStream out(&outputFile);
    out << QString("Progress:\n");
    out << QString::number(progress) << "\n";
    out << QString("Number of items:\n");
    out << QString::number(numItems) << "\n";
    out << QString("X Coordinates:\n");
    for( int i = 0 ; i < numItems ; ++i )
    {
        out << QString::number(xCoords[i]) << "\n";
    }
    out << QString("Y Coordinates:\n");
    for( int i = 0 ; i < numItems ; ++i )
    {
        out << QString::number(yCoords[i]) << "\n";
    }
    out << QString("Z Coordinates:\n");
    for( int i = 0 ; i < numItems ; ++i )
    {
        out << QString::number(zCoords[i]) << "\n";
    }
    out << QString("Rotations:\n");
    for( int i = 0 ; i < numItems ; ++i )
    {
        out << QString::number(rotations[i]) << "\n";
    }
    outputFile.close();
}
