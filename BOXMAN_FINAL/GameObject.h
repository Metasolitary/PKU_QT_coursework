#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
//Object��������һ����Ϸʵ��ĸ���
class GameObject {
public:
    int x;  // ����ĺ�����
    int y;  // �����������
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
