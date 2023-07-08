#ifndef MAINWINDOW_H1
#define MAINWINDOW_H1


#include"Vacuum.h"
#include"Wall.h"
#include"Floor.h"
#include"Person.h"
#include"Box.h"
#include"Destination.h"
#include"Map.h"
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QFont>
#include <QPen>
#include "newbutton.h"

#define INTERFACE_WIDTH 740 // 窗口宽度
#define INTERFACE_HEIGHT 740 // 窗口高度
#define INTERFACE_WIDTH1 925 // 窗口宽度
#define INTERFACE_HEIGHT1 555 // 窗口高度
#define LINE1 6 // 地图行数
#define COLUMN1 10 // 地图列数
#define SIZE 61 // 单元格尺寸
#define BACKGROUND_PATH ":/pics/background" // 背景图片
#define WALL_PATH ":/pics/wall" // 墙图片
#define FLOOR_PATH ":/pics/floor" // 地板图片
#define DES_PATH ":/pics/des" // 目标地点图片
#define MAN_PATH ":/pics/agent" // 人物图片
#define BOX_PATH ":/pics/box" // 箱子图片
#define PORTAL_PATH ":/pics/portal"//
#define MAX_STEP 50 // 最大步数限制
#define X_SHIFT 110 // x偏移量
#define Y_SHIFT 130 // y偏移量

namespace Ui {
class game1;
}

class game1 : public QWidget
{
    Q_OBJECT
private:
    Ui::game1 *ui;
    int step_count;
    NewButton* Return;
    QVBoxLayout *L1;
    QHBoxLayout *L2;
public:
    explicit game1(QWidget *parent = nullptr);
    ~game1();
protected:
    void paintEvent(QPaintEvent *);//接受更新信号，并重新渲染界面
    void keyPressEvent(QKeyEvent *);//接受键盘输入，并更新map数据，发出更新信号
    void map_initailization();
public slots:
    void gameOver_after();
    void gameSuccess_after();
    void returnclicked();

signals:
    void refresh();//每次object位置更新后发出该信号
    void gameover();
    void gamesuccess();



};

#endif // MAINWINDOW_H
