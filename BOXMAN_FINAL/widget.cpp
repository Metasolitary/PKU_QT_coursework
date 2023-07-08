#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Choose!");
    this->setWindowIcon(QIcon(":/pics/icon.jpeg"));
    title = new QLabel;
    space = new QLabel;
    b1 = new NewButton;
    b2 = new NewButton;
    b3 = new NewButton;
    b4 = new NewButton;
    b5 = new NewButton;
    b6 = new NewButton;
    b7 = new NewButton;
    b8 = new NewButton;
    b1->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    b2->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    b3->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    b4->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    b5->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    b6->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    b7->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    b8->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");

    title->setText("L\nE\nV\nE\nL\nS\n");
    title->setFont(QFont("Wide Latin", 40));
    space->setText("          ");
    space->setFont(QFont("Wide Latin", 40));
    title->setStyleSheet("color:white;");
    L = new QHBoxLayout;
    L->addWidget(title, 1, Qt::AlignCenter);
    L->addWidget(space, 1, Qt::AlignCenter);
    b1->setText("1");
    b2->setText("2");
    b3->setText("3");
    b4->setText("4");
    b5->setText("5");
    b6->setText("6");
    b7->setText("7");
    b8->setText("8");
    b1->setFont(QFont("Wide Latin", 18));
    b2->setFont(QFont("Wide Latin", 18));
    b3->setFont(QFont("Wide Latin", 18));
    b4->setFont(QFont("Wide Latin", 18));
    b5->setFont(QFont("Wide Latin", 18));
    b6->setFont(QFont("Wide Latin", 18));
    b7->setFont(QFont("Wide Latin", 18));
    b8->setFont(QFont("Wide Latin", 18));
    b1->setFixedSize(100, 150);
    b2->setFixedSize(100, 150);
    b3->setFixedSize(100, 150);
    b4->setFixedSize(100, 150);
    b5->setFixedSize(100, 150);
    b6->setFixedSize(100, 150);
    b7->setFixedSize(100, 150);
    b8->setFixedSize(100, 150);


    L1 = new QVBoxLayout;
    L2 = new QVBoxLayout;
    L3 = new QVBoxLayout;
    L4 = new QVBoxLayout;


    L1->addWidget(b1);
    L1->addWidget(b2);
    L1->addWidget(b3);
    L1->addWidget(b4);
    L2->addWidget(b5);
    L2->addWidget(b6);
    L2->addWidget(b7);
    L2->addWidget(b8);
    L->addLayout(L1);
    L->addLayout(L2);
    //L->addLayout(L3);
   // L->addLayout(L4);
    this->setLayout(L);

    connect(b1,&QPushButton::clicked,this,&Widget::oneclicked);
    connect(b2,&QPushButton::clicked,this,&Widget::twoclicked);
    connect(b3,&QPushButton::clicked,this,&Widget::threeclicked);
    connect(b4,&QPushButton::clicked,this,&Widget::fourclicked);
    connect(b5,&QPushButton::clicked,this,&Widget::fiveclicked);
    connect(b6,&QPushButton::clicked,this,&Widget::sixclicked);
    connect(b7,&QPushButton::clicked,this,&Widget::sevenclicked);
    connect(b8,&QPushButton::clicked,this,&Widget::eightclicked);

        resize(1000, 1000);

}

void Widget::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.drawPixmap(this->rect() ,QPixmap(":/pics/ggbond2.jpeg"));

}
void Widget::oneclicked()
{
    game1 *g=new game1;
    g->show();
    this->close();
}
void Widget::twoclicked()
{
    game2 *g=new game2;
    g->show();
    this->close();
}
void Widget::threeclicked()
{
    game3 *g=new game3;
    g->show();
    this->close();
}
void Widget::fourclicked()
{
    game4 *g=new game4;
    g->show();
    this->close();
}
void Widget::fiveclicked()
{
    game5 *g=new game5;
    g->show();
    this->close();
}
void Widget::sixclicked()
{
    game6 *g=new game6;
    g->show();
    this->close();

}
void Widget::sevenclicked()
{
    game7 *g=new game7;
    g->show();
    this->close();

}
void Widget::eightclicked()
{
    game8 *g=new game8;
    g->show();
    this->close();
}
Widget::~Widget()
{
    delete ui;
}
