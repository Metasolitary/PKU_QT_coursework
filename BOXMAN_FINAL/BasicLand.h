#ifndef BASICLAND_H
#define BASICLAND_H
#include "GameObject.h"
class Map;
class BasicLand :
    public GameObject
{
public:
    BasicLand(int x, int y) : GameObject(x, y) {}
    virtual void accept(GameObject* a, Map* b) {};
    virtual bool acceptable() = 0;
};

#endif // !BASICLAND_H