#ifndef FAKEWALL_H

#include "Floor.h"
class FakeWall :
    public Floor
{
public:
    bool found = false;
    FakeWall(int x, int y) :Floor(x, y) {}
    void virtual accept(GameObject* a, Map* m);
    bool virtual acceptable();
};

#endif // !FAKEWALL_H



