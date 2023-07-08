#include "game3.h"
#include "ui_game3.h"
#include <widget.h>


static GameInfo test(11,4,1,2,3,  { {2,2}, {5,1},{8,2} },2, { {{3,2},{6,1}},{{4,1},{7,2}} },
                         {
                         {1,1,1,1},
                                 {1,0,0,1},
                                 {1,0,0,1},
                                {1,0,0,1},
                                 {1,0,0,1},
                                 {1,0,0,1},
                                 {1,0,0,1},
                             {1,0,0,1},
                             {1,0,0,1},
                             {1,0,0,1},
                             {1,1,1,1}
                             },{ {2,1},{5,2},{8,1} },3);

static GameInfo last(11,4,1,2,3,  { {2,2}, {5,1},{8,2} },2, { {{3,2},{6,1}},{{4,1},{7,2}} },
{
{1,1,1,1},
        {1,0,0,1},
        {1,0,0,1},
       {1,0,0,1},
        {1,0,0,1},
        {1,0,0,1},
        {1,0,0,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1}
    },{ {2,1},{5,2},{8,1} },3);
static Map testmap(test);//测试关信息
static bool first=1;
static bool end=0;
game3::game3(QWidget *parent) :
    QWidget(parent)

{

    map_initailization();
    connect(this, SIGNAL(refresh()), this, SLOT(update()));//update()调用paintevent
    connect(this, SIGNAL(gameover()), this, SLOT(gameOver_after()));
    connect(this, SIGNAL(gamesuccess()), this, SLOT(gameSuccess_after()));
    connect(Return,SIGNAL(clicked()),this,SLOT(returnclicked()));
};
game3::~game3()
{

}


void game3::map_initailization() {

    setWindowTitle("Level3");
    this->setWindowIcon(QIcon(":/pics/icon.jpeg"));
    step_count = 0;
    Return = new NewButton(this);

     Return->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
     Return->setText("Return!");
     Return->setFont(QFont("Wide Latin", 20));
     L1 = new QVBoxLayout;
     L1->setAlignment(Qt::AlignBottom);
     L1->addWidget(Return);
     QWidget *spacer = new QWidget();
     spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     L1->addWidget(spacer);

     this->setLayout(L1);
     resize(INTERFACE_WIDTH3-20, INTERFACE_HEIGHT3);

}
void game3::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(this->rect(), QPixmap(BACKGROUND_PATH3)); // 绘制背景
    QFont font("微软雅黑", 15, QFont::ExtraLight, false);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.setFont(font);

    for (int i = 0; i < LINE3; i++) {
        for (int j = 0; j < COLUMN3; j++) {
            if
                (dynamic_cast<Box*>(testmap.Upper_map[i][j])) {
                painter.drawPixmap(X_SHIFT3 + SIZE3 * j, Y_SHIFT3 + SIZE3 * i, SIZE3, SIZE3, QPixmap(BOX_PATH3)); // 绘制箱子
            }
            else if
                (dynamic_cast<Person*>(testmap.Upper_map[i][j]))
            {
                painter.drawPixmap(X_SHIFT3 + SIZE3 * j, Y_SHIFT3 + SIZE3 * i, SIZE3, SIZE3, QPixmap(MAN_PATH3)); // 绘制人
            }
            else if
                    (dynamic_cast<Destination*>(testmap.Lower_map[i][j])) {
                    painter.drawPixmap(X_SHIFT3 + SIZE3 * j, Y_SHIFT3 + SIZE3 * i, SIZE3, SIZE3, QPixmap(DES_PATH3)); // 绘制目的地
            }
            else if
                (dynamic_cast<Wall*> (testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT3 + SIZE3 * j, Y_SHIFT3 + SIZE3 * i, SIZE3, SIZE3, QPixmap(WALL_PATH3)); // 绘制墙
            }
            else if
                (dynamic_cast<Vacuum*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT3 + SIZE3 * j, Y_SHIFT3 + SIZE3 * i, SIZE3, SIZE3, QPixmap(FLOOR_PATH3)); // 绘制目的地
            }
            else if

                (dynamic_cast<Floor*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT3 + SIZE3 * j, Y_SHIFT3 + SIZE3* i, SIZE3, SIZE3, QPixmap(FLOOR_PATH3)); // 绘制空地
            }
            else if

                (dynamic_cast<Portal*>(testmap.Lower_map[i][j])) {
                painter.drawPixmap(X_SHIFT3 + SIZE3 * j, Y_SHIFT3 + SIZE3 * i, SIZE3, SIZE3, QPixmap(PORTAL_PATH3)); // 绘制传送门
            }

        }
    }
    if (testmap.win_judge()) {
        painter.drawText(150,900, QString("任务成功！"));
        emit gamesuccess();
        return;
    }
    if (step_count > MAX_STEP3) {
        painter.drawText(150, 900, QString("任务失败！"));
        emit gameover();
        return;
    }
    painter.drawText(80, 980, QString("剩余步数：%1").arg(MAX_STEP3 - step_count));

}

void game3::keyPressEvent(QKeyEvent *event) {
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
void game3::gameOver_after() {
    end=1;
    disconnect(this, SIGNAL(refresh()), this, SLOT(update()));
}

void game3::gameSuccess_after() {
    end=1;
    disconnect(this, SIGNAL(refresh()), this, SLOT(update()));
}
void game3::returnclicked(){
    Widget *c = new Widget;
    c->show();
    this->close();
}
