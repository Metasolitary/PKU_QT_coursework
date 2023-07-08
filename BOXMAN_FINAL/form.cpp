#include "form.h"
#include "ui_form.h"
#define INTERFACE_WIDTH 960 // 窗口宽度
#define INTERFACE_HEIGHT 768 // 窗口高度
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setWindowTitle("content");
    resize(INTERFACE_WIDTH, INTERFACE_HEIGHT);

}

Form::~Form()
{
    delete ui;

}
