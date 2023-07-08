#include "FakeWall.h"
#include<iostream>
void FakeWall::accept(GameObject* a, Map* m) {
    if (m->Upper_map[x][y] != nullptr) {
        std::cout<< "error code";
        return;
    }
    found = true;
    m->Upper_map[a->x][a->y] = nullptr;
    m->Upper_map[x][y] = a;
    a->x = x;
    a->y = y;
    return;
}
bool FakeWall::acceptable() { return true; };