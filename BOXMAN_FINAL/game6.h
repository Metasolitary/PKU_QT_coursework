#ifndef MAINWINDOW_H6
#define MAINWINDOW_H6


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

#define INTERFACE_WIDTH06 740 // 窗口宽度
#define INTERFACE_HEIGHT06 740 // 窗口高度
#define INTERFACE_WIDTH6 680 // 窗口宽度
#define INTERFACE_HEIGHT6 800 // 窗口高度
#define LINE6 6 // 地图行数
#define COLUMN6 9 // 地图列数
#define SIZE6 61 // 单元格尺寸
#define BACKGROUND_PATH6 ":/pics/background" // 背景图片
#define WALL_PATH6 ":/pics/wall" // 墙图片
#define FLOOR_PATH6 ":/pics/floor" // 地板图片
#define DES_PATH6 ":/pics/des" // 目标地点图片
#define MAN_PATH6 ":/pics/agent" // 人物图片
#define BOX_PATH6 ":/pics/box" // 箱子图片
#define PORTAL_PATH6 ":/pics/portal"//
#define MAX_STEP6 100 // 最大步数限制
#define X_SHIFT6 110 // x偏移量
#define Y_SHIFT6 130 // y偏移量

namespace Ui {
class game6;
}

class game6 : public QWidget
{
    Q_OBJECT
private:
    Ui::game6 *ui;
    int step_count;
    NewButton* Return;
    QVBoxLayout *L1;
    QHBoxLayout *L2;
public:
    explicit game6(QWidget *parent = nullptr);
    ~game6();
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
