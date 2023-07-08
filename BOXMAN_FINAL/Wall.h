#ifndef WALL_H
#define WALL_H
#include "BasicLand.h"
#include"Map.h"
class Wall :
    public BasicLand
{
public:
    Wall(int x, int y) : BasicLand(x, y) {}
    virtual void accept(GameObject*a, Map*b);
    virtual bool acceptable();
};

#endif // !WALL
