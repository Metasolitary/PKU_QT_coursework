#include "Floor.h"
#include<iostream>
void Floor::accept(GameObject* a,Map* m) {
    if (m->Upper_map[x][y] != nullptr) {
        std::cout << "error code";
        return;
    }
    m->Upper_map[a->x][a->y] = nullptr;
    m->Upper_map[x][y] = a;
    a->x = x;
    a->y = y;
    
    return;
}
bool Floor::acceptable() { return true; }
