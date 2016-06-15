#ifndef COORDINATES_H
#define COORDINATES_H
#include <QDebug>
class Coordinates
{
public:
    int x;
    int y;
    int z;
    Coordinates(int initialX, int initialY, int initialZ) :
        x(initialX),
        y(initialY),
        z(initialZ) {}
    bool operator == (Coordinates arg)
    {
        if( (x == arg.x) &&
            (y == arg.y) &&
            (z == arg.z) )
            return true;
        else
            return false;
    }
private:
    Coordinates();
};

#endif // COORDINATES_H
