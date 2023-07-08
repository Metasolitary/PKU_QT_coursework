#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include "newbutton.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>



#include"game1.h"
#include"game2.h"
#include"game3.h"
#include"game4.h"
#include"game5.h"
#include"game6.h"
#include"game7.h"
#include"game8.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent* event);


private:
    Ui::Widget *ui;
    QLabel* title;
    QLabel* space;
    NewButton* b1;
    NewButton* b2;
    NewButton* b3;
    NewButton* b4;
    NewButton* b5;
    NewButton* b6;
    NewButton* b7;
    NewButton* b8;
    QVBoxLayout *L1;
    QVBoxLayout*L2;
    QVBoxLayout*L3;
    QVBoxLayout*L4;
    QHBoxLayout *L;

public slots:
    void oneclicked();
    void twoclicked();
    void threeclicked();
    void fourclicked();
    void fiveclicked();
    void sixclicked();
    void sevenclicked();
    void eightclicked();

};

#endif // WIDGET_H
