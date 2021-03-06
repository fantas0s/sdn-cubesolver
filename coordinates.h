#ifndef COORDINATES_H
#define COORDINATES_H
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
    Coordinates() :
        x(0),
        y(0),
        z(0) {}
    bool operator == (const Coordinates arg) const
    {
        if( (x == arg.x) &&
            (y == arg.y) &&
            (z == arg.z) )
            return true;
        else
            return false;
    }
    bool operator > (const Coordinates arg) const
    {
        if( (x >= arg.x) &&
            (y >= arg.y) &&
            (z >= arg.z) )
            return true;
        else
            return false;
    }
private:
};

#endif // COORDINATES_H
