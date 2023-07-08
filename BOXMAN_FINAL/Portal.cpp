#include "Portal.h"
void Portal::accept(GameObject* a,Map*m) {
    BasicLand* temp = (BasicLand*)cor_portal;
    if (m->Upper_map[temp->x][temp->y] != nullptr) {
        m->Upper_map[a->x][a->y] = nullptr;
        m->Upper_map[x][y] = a;
        a->x = x;
        a->y = y;
        return;
    }
    else {
        m->Upper_map[a->x][a->y] = nullptr;
        m->Upper_map[temp->x][temp->y] = a;
        a->x = temp->x;
        a->y = temp->y;
        m->Upper_map[x][y] = nullptr;
        return;
    }
}
bool Portal::acceptable() { return true; }
