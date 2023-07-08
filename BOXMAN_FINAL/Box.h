#ifndef BOX_H
#define BOX_H


#include "GameObject.h"
class Box :
    public GameObject
{
private:
    int num;//Ïä×ÓµÄ±àºÅ
public:
    Box(int x, int y) : GameObject(x, y) {}
    //bool check_collision(GameObject obj);
    int get_num();
    void set_num(int n);
};

#endif // !BOX_H