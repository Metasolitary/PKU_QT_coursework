#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMediaPlayer>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QFont>
#include <QPen>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "newbutton.h"
#include <QMessageBox>
#include <QProcess>
#include<QMediaPlaylist>
#include<QSoundEffect>
//#include "form.h"
//#include "ui_form.h"
#include "widget.h"

#define INTERFACE_WIDTH 960 // 窗口宽度
#define INTERFACE_HEIGHT 768 // 窗口高度
#define LINE 9 // 地图行数
#define COLUMN 12 // 地图列数
#define SIZE 61 // 单元格尺寸
#define BACKGROUND_PATH ":/pics/background" // 背景图片
#define WALL_PATH ":/pics/wall" // 墙图片
#define FLOOR_PATH ":/pics/floor" // 地板图片
#define DES_PATH ":/pics/des" // 目标地点图片
#define MAN_PATH ":/pics/agent" // 人物图片
#define BOX_PATH ":/pics/box" // 箱子图片
#define MAX_STEP 1000 // 最大步数限制
#define X_SHIFT 110 // x偏移量
#define Y_SHIFT 130 // y偏移量

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();
    QMediaPlayer* player;
    QMediaPlaylist* playlist;

protected:
    void paintEvent(QPaintEvent* );

private:
    Ui::MainWindow *ui;
    //Form* nxt;
    NewButton* st;
    NewButton* ex;
    QVBoxLayout* layout;
    QWidget* widget;
    QLabel* label;
    //QSoundEffect* music;
    Widget* wi;
private slots:
    void windowswitched();
    void windowclosed();
};

#endif // MAINWINDOW_H
