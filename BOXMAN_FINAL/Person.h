#ifndef PERSON_H
#define PERSON_H
#include "GameObject.h"
class Person :
    public GameObject
{
public:
    Person(int x, int y) : GameObject(x, y) {}
 /*   void move(int x, int y);
    void push_box();
    bool check_collision(GameObject obj);*/
};
#endif // !PERSON_H
