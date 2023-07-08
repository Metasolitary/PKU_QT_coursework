#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newbutton.h"
#include "widget.h"
#include "ui_widget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("GG Box!");
    this->setWindowIcon(QIcon(":/pics/icon.jpeg"));
    init();
    connect(ex, SIGNAL(clicked()), this, SLOT(windowclosed()));
    connect(st, SIGNAL(clicked()), this, SLOT(windowswitched()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){

    resize(INTERFACE_WIDTH+1600-INTERFACE_WIDTH, INTERFACE_HEIGHT+1000-INTERFACE_HEIGHT);
    label = new QLabel;
    label->setFont(QFont("Wide Latin", 30));
    label->setText("GG\nBOX!");
    label->setStyleSheet("color:red;");

    st = new NewButton(this);
    st->setFixedSize(300, 200);

    st->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    st->setText("Start!");
    st->setFont(QFont("Wide Latin", 23));

    ;

    ex = new NewButton(this);


    ex->setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    ex->setFixedSize(300, 200);
    ex->setText("Exit!");
    ex->setFont(QFont("Wide Latin", 25));


    layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(st);

    layout->addWidget(ex);

    layout->setAlignment(Qt::AlignRight);

    widget = new QWidget;
    widget->setLayout(layout);
    wi = new Widget;
    QMediaPlayer * music = new QMediaPlayer ();
     music->setMedia (QUrl ("qrc:/pics/Gymnopédie no. 1 (for Harp).mp3"));
    music->play ();

}

void MainWindow::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.drawPixmap(this->rect(), QPixmap(":/pics/ggbond.jpg"));
    this->setCentralWidget(widget);
    this->layout->layout()->setAlignment(Qt::AlignRight);
}
void MainWindow::windowclosed(){
    this->close();
}
void MainWindow::windowswitched(){
    this->hide();
    wi->show();
}
