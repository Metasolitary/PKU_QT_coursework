#include "game4.h"
#include "ui_game4.h"
#include <widget.h>


static GameInfo test(7,7,3,3,4, { {2,3}, {3,2},{3,4},{4,3} },2, { {{4,4},{2,2}},{{4,2},{2,4}} },
                         {
                         {1,1,1,1,1,1,1},
                                 {1,0,0,0,1,0,1},
                                 {1,1,0,0,0,0,1},
                                 {1,0,0,0,0,0,1},
                                 {1,0,0,0,0,0,1},
                                 {1,0,1,0,0,0,1},
                                 {1,1,1,1,1,1,1}
                             },{ {1,1},{1,5},{5,1},{5,5} },4);

static GameInfo last(7,7,3,3,4, { {2,3}, {3,2},{3,4},{4,3} },2, { {{4,4},{2,2}},{{4,2},{2,4}} },
{
{1,1,1,1,1,1,1},
        {1,0,0,0,1,0,1},
        {1,1,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,1,0,0,0,1},
        {1,1,1,1,1,1,1}
    },{ {1,1},{1,5},{5,1},{5,5} },4);
static Map testmap(test);//测试关信息
static bool first=1;
static bool end=0;
game4::game4(QWidget *parent) :
    QWidget(parent)

{

    map_initailization();
    connect(this, SIGNAL(refresh()), this, SLOT(update()));//update()调用paintevent
    connect(this, SIGNAL(gameover()), this, SLOT(gameOver_after()));
    connect(this, SIGNAL(gamesuccess()), this, SLOT(gameSuccess_after()));
    connect(Return,SIGNAL(clicked()),this,SLOT(returnclicked()));
};
game4::~game4()
{

}


void game4::map_initailization() {
    resize(INTERFACE_WIDTH4, INTERFACE_HEIGHT4);
    setWindowTitle("Level4");
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
void game4::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(this->rect(), QPixmap(BACKGROUND_PATH4)); // 绘制背景
    QFont font("微软雅黑", 30, QFont::ExtraLight, false);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.setFont(font);

    for (int i = 0; i < LINE4; i++) {
        for (int j = 0; j < COLUMN4; j++) {
            if
                (dynamic_cast<Box*>(testmap.Upper_map[i][j])) {
                painter.drawPixmap(X_SHIFT4 + SIZE4 * j, Y_SHIFT4 + SIZE4 * i, SIZE4, SIZE4, QPixmap(BOX_PATH4)); // 绘制箱子
            }
            else if
                (dynamic_cast<Person*>(testmap.Upper_map[i][j]))
            {
                painter.drawPixmap(X_SHIFT4 + SIZE4 * j, Y_SHIFT4 + SIZE4 * i, SIZE4, SIZE4, QPixmap(MAN_PATH4)); // 绘制人
            }
            else if
                    (dynamic_cast<Destination*>(testmap.Lower_map[i][j])) {
                    painter.drawPixmap(X_SHIFT4+ SIZE4 * j, Y_SHIFT4 + SIZE4 * i, SIZE4, SIZE4, QPixmap(DES_PATH4)); // 绘制目的地
            }
            else if
                (dynamic_cast<Wall*> (testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT4 + SIZE4 * j, Y_SHIFT4 + SIZE4 * i, SIZE4, SIZE4, QPixmap(WALL_PATH4)); // 绘制墙
            }
            else if
                (dynamic_cast<Vacuum*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT4 + SIZE4 * j, Y_SHIFT4 + SIZE4 * i, SIZE4, SIZE4, QPixmap(FLOOR_PATH4)); // 绘制目的地
            }
            else if

                (dynamic_cast<Floor*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT4 + SIZE4 * j, Y_SHIFT4 + SIZE4 * i, SIZE4, SIZE4, QPixmap(FLOOR_PATH4)); // 绘制空地
            }
            else if

                (dynamic_cast<Portal*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT4 + SIZE4 * j, Y_SHIFT4 + SIZE4 * i, SIZE4, SIZE4, QPixmap(PORTAL_PATH4)); // 绘制传送门
            }

        }
    }
    if (testmap.win_judge()) {
        painter.drawText(100, 640, QString("任务成功！"));
        emit gamesuccess();
        return;
    }
    if (step_count > MAX_STEP4) {
        painter.drawText(100, 640, QString("任务失败！"));
        emit gameover();
        return;
    }
    painter.drawText(40, 640, QString("剩余步数：%1").arg(MAX_STEP4 - step_count));

}

void game4::keyPressEvent(QKeyEvent *event) {
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
void game4::gameOver_after() {
    end=1;
    disconnect(this, SIGNAL(refresh()), this, SLOT(update()));
}

void game4::gameSuccess_after() {
    end=1;
    disconnect(this, SIGNAL(refresh()), this, SLOT(update()));
}
void game4::returnclicked(){
    Widget *c = new Widget;
    c->show();
    this->close();
}
