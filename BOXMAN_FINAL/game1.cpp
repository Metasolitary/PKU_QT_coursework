#include "game1.h"
#include "ui_game1.h"
#include<widget.h>


static GameInfo test(6,10,3,5,4, { {3,3},{4,3},{3,6},{4,6} },2, { { {3,2},{4,7} }, { {4,2},{3,7} } },
                         {
                                 {2,2,2,1,1,1,1,2,2,2},
                                 {2,2,2,1,0,0,1,2,2,2},
                                 {1,1,1,1,0,0,1,1,1,1},
                                 {1,0,0,0,0,0,0,0,0,1},
                                 {1,0,0,0,0,0,0,0,0,1},
                                 {1,1,1,1,1,1,1,1,1,1}
                             },{ {1,4 },{1,5},{2,4},{2,5} },4);

static GameInfo last(6,10,3,5,4, { {3,3},{4,3},{3,6},{4,6} },2, { { {3,2},{4,7} }, { {4,2},{3,7} } },
{
        {2,2,2,1,1,1,1,2,2,2},
        {2,2,2,1,0,0,1,2,2,2},
        {1,1,1,1,0,0,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    },{ {1,4 },{1,5},{2,4},{2,5} },4);
static Map testmap(test);//测试关信息
static bool first=1;
static bool end=0;
game1::game1(QWidget *parent) :
    QWidget(parent)

{

    map_initailization();
    connect(this, SIGNAL(refresh()), this, SLOT(update()));//update()调用paintevent
    connect(this, SIGNAL(gameover()), this, SLOT(gameOver_after()));
    connect(this, SIGNAL(gamesuccess()), this, SLOT(gameSuccess_after()));
    connect(Return,SIGNAL(clicked()),this,SLOT(returnclicked()));
};
game1::~game1()
{

}


void game1::map_initailization() {
    resize(INTERFACE_WIDTH1-70, INTERFACE_HEIGHT1+100);
    setWindowTitle("Level1");
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
void game1::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(this->rect(), QPixmap(BACKGROUND_PATH)); // 绘制背景
    QFont font("微软雅黑", 30, QFont::ExtraLight, false);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.setFont(font);

    for (int i = 0; i < LINE1; i++) {
        for (int j = 0; j < COLUMN1; j++) {
            if
                (dynamic_cast<Box*>(testmap.Upper_map[i][j])) {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(BOX_PATH)); // 绘制箱子
            }
            else if
                (dynamic_cast<Person*>(testmap.Upper_map[i][j]))
            {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(MAN_PATH)); // 绘制人
            }
            else if
                    (dynamic_cast<Destination*>(testmap.Lower_map[i][j])) {
                    painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(DES_PATH)); // 绘制目的地
            }
            else if
                (dynamic_cast<Wall*> (testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(WALL_PATH)); // 绘制墙
            }
            else if
                (dynamic_cast<Vacuum*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(FLOOR_PATH)); // 绘制目的地
            }
            else if

                (dynamic_cast<Floor*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(FLOOR_PATH)); // 绘制空地
            }
            else if

                (dynamic_cast<Portal*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(PORTAL_PATH)); // 绘制传送门
            }

        }
    }
    if (testmap.win_judge()) {
        painter.drawText(120, 600,QString("任务成功！"));
        emit gamesuccess();
        return;
    }
    if (step_count > MAX_STEP) {
        painter.drawText(120, 600, QString("任务失败！"));
        emit gameover();
        return;
    }
        painter.drawText(120, 600, QString("剩余步数：%1").arg(MAX_STEP - step_count));

}

void game1::keyPressEvent(QKeyEvent *event) {
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
void game1::gameOver_after() {
    end=1;
    disconnect(this, SIGNAL(refresh()), this, SLOT(update()));
}

void game1::gameSuccess_after() {
    end=1;
    disconnect(this, SIGNAL(refresh()), this, SLOT(update()));
}
void game1::returnclicked(){
    Widget *c = new Widget;
    c->show();
    this->close();
}
