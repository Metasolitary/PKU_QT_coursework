#ifndef FLOOR_H
#define FLOOR_H


#include "BasicLand.h"
#include"Map.h"
class Floor :
 public BasicLand
{
public:
    Floor(int x, int y) : BasicLand(x, y) {}
    virtual void accept(GameObject* a,  Map*b);
    virtual bool acceptable();
};

#endif // !FLOOR_H