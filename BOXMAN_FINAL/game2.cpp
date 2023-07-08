#include "game2.h"
#include "ui_game2.h"
#include<widget.h>


static GameInfo test(10,7,2,3,3,  { {3,2},{3,3},{3,4} },1, { {{4,3},{8,3}} },
                         {
                         {1,1,2,2,2,1,1},
                                 {1,0,1,1,1,0,1},
                                 {1,0,0,0,0,0,1,},
                                 {1,0,0,0,0,0,1,},
                                 {2,1,1,0,1,1,2},
                                 {2,1,0,0,1,1,2},
                                 {1,0,0,0,0,0,1},
                                 {1,0,0,0,0,0,1},
                                 {1,0,0,0,0,0,1},
                                 {2,1,1,1,1,1,2}
                             }, { {7,2},{7,4} },2);

static GameInfo last(10,7,2,3,3,  { {3,2},{3,3},{3,4} },1, { {{4,3},{8,3}} },
{
{1,1,2,2,2,1,1},
        {1,0,1,1,1,0,1},
        {1,0,0,0,0,0,1,},
        {1,0,0,0,0,0,1,},
        {2,1,1,0,1,1,2},
        {2,1,0,0,1,1,2},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {2,1,1,1,1,1,2}
    }, { {7,2},{7,4} },2);
static Map testmap(test);//测试关信息
static bool first=1;
static bool end=0;
game2::game2(QWidget *parent) :
    QWidget(parent)

{

    map_initailization();
    connect(this, SIGNAL(refresh()), this, SLOT(update()));//update()调用paintevent
    connect(this, SIGNAL(gameover()), this, SLOT(gameOver_after()));
    connect(this, SIGNAL(gamesuccess()), this, SLOT(gameSuccess_after()));
    connect(Return,SIGNAL(clicked()),this,SLOT(returnclicked()));
};
game2::~game2()
{

}


void game2::map_initailization() {
    resize(INTERFACE_WIDTH2, INTERFACE_HEIGHT2);
    setWindowTitle("Level2");
    this->setWindowIcon(QIcon(":/pics/icon.jpeg"));
    step_count = 0;
    Return = new NewButton(this);

     Return->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
     Return->setText("Return!");
     Return->setFont(QFont("Wide Latin", 25));
     L1 = new QVBoxLayout;
     L1->setAlignment(Qt::AlignBottom);
     L1->addWidget(Return);
     QWidget *spacer = new QWidget();
     spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     L1->addWidget(spacer);

     this->setLayout(L1);

}
void game2::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(this->rect(), QPixmap(BACKGROUND_PATH2)); // 绘制背景
    QFont font("微软雅黑", 30, QFont::ExtraLight, false);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.setFont(font);

    for (int i = 0; i < LINE2; i++) {
        for (int j = 0; j < COLUMN2; j++) {
            if
                (dynamic_cast<Box*>(testmap.Upper_map[i][j])) {
                painter.drawPixmap(X_SHIFT2 + SIZE2 * j, Y_SHIFT2 + SIZE2 * i, SIZE2, SIZE2, QPixmap(BOX_PATH2)); // 绘制箱子
            }
            else if
                (dynamic_cast<Person*>(testmap.Upper_map[i][j]))
            {
                painter.drawPixmap(X_SHIFT2+ SIZE2 * j, Y_SHIFT2 + SIZE2 * i, SIZE2, SIZE2, QPixmap(MAN_PATH2)); // 绘制人
            }
            else if
                    (dynamic_cast<Destination*>(testmap.Lower_map[i][j])) {
                    painter.drawPixmap(X_SHIFT2 + SIZE2 * j, Y_SHIFT2 + SIZE2 * i, SIZE2, SIZE2, QPixmap(DES_PATH2)); // 绘制目的地
            }
            else if
                (dynamic_cast<Wall*> (testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT2 + SIZE2 * j, Y_SHIFT2 + SIZE2 * i, SIZE2, SIZE2, QPixmap(WALL_PATH2)); // 绘制墙
            }
            else if
                (dynamic_cast<Vacuum*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT2 + SIZE2 * j, Y_SHIFT2 + SIZE2 * i, SIZE2, SIZE2, QPixmap(FLOOR_PATH2)); // 绘制目的地
            }
            else if

                (dynamic_cast<Floor*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT2 + SIZE2 * j, Y_SHIFT2 + SIZE2 * i, SIZE2, SIZE2, QPixmap(FLOOR_PATH2)); // 绘制空地
            }
            else if

                (dynamic_cast<Portal*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT2 + SIZE2 * j, Y_SHIFT2 + SIZE2 * i, SIZE2, SIZE2, QPixmap(PORTAL_PATH2)); // 绘制传送门
            }

        }
    }
    if (testmap.win_judge()) {
        painter.drawText(40, 900, QString("任务成功！"));
        emit gamesuccess();
        return;
    }
    if (step_count > MAX_STEP2) {
        painter.drawText(40, 900, QString("任务失败！"));
        emit gameover();
        return;
    }
painter.drawText(40, 900, QString("剩余步数：%1").arg(MAX_STEP2 - step_count));
}

void game2::keyPressEvent(QKeyEvent *event) {
    if(!end)
    {if (event->key() == Qt::Key_W) {
        testmap.save_gameinfo(last);
        testmap.person_move(0);step_count++;first=1;
        emit refresh();//输入W后的更新
    } else if (event->key() == Qt::Key_A) {
        testmap.save_gameinfo(last);
        testmap.person_move(3);step_count++;first=1;
        emit refresh();//输入A后的更新
    } else if (event->key() == Qt::Key_D) {
        testmap.save_gameinfo(last);
        testmap.person_move(1);step_count++;first=1;
        emit refresh();//输入D后的更新
    } else if (event->key() == Qt::Key_S) {
        testmap.save_gameinfo(last);
        testmap.person_move(2);step_count++;first=1;
        emit refresh();//输入S后的更新
    } else if (event->key() == Qt::Key_R) {     
        testmap.reset_map(test);
        testmap.save_gameinfo(last);
        step_count=0;emit refresh();
    } else if(event->key() == Qt::Key_E){
        if(first)
        {testmap.reset_map(last);
        if(step_count!=0)
        {
            step_count--;
        }
        emit refresh();first=0;
        }
    }
    }
}
void game2::gameOver_after() {
    end=1;
    disconnect(this, SIGNAL(refresh()), this, SLOT(update()));
}

void game2::gameSuccess_after() {
    end=1;
    disconnect(this, SIGNAL(refresh()), this, SLOT(update()));
}
void game2::returnclicked(){
    Widget *c = new Widget;
    c->show();
    this->close();
}
