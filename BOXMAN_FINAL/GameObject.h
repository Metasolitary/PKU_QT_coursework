#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
//Object类是所有一切游戏实体的父类
class GameObject {
public:
    int x;  // 物体的横坐标
    int y;  // 物体的纵坐标
public:
    GameObject(int x, int y) :x(x), y(y) {}

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void setX(int x) {
        x = x;
    }

    void setY(int y) {
        y = y;
    }
    virtual bool check_collision(GameObject obj) 
    { return getX() == obj.getX() && getY() == obj.getY(); }
};
#endif // !GAMEOBJECT_H
