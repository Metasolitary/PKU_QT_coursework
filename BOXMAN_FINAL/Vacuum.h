#ifndef VACUUM_H
#define VACUUM_H

#include "BasicLand.h"
#include"Map.h"
class Vacuum :
    public BasicLand
{
public:
    Vacuum(int x, int y) :BasicLand(x, y) {};
    virtual void accept(GameObject*a, Map*b);
    virtual bool acceptable();
};

#endif // !VACUUM_H