#ifndef PORTAL_H
#define PORTAL_H

#include"BasicLand.h"
#include"Map.h"
class Portal :
    public BasicLand
{
public:
    void* cor_portal;
    Portal(int x, int y) :BasicLand(x, y) {};
    virtual void accept(GameObject*a, Map*b);
    virtual bool acceptable();
};
#endif // !PORTAL_H




