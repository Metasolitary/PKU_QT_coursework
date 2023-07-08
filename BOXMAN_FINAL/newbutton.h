#ifndef NEWBUTTON_H

#define NEWBUTTON_H
#pragma once
#include <QPushButton>
#include <QEvent>
#include <QObject>

class NewButton: public QPushButton
{
    Q_OBJECT

public:
    NewButton(QWidget* parent = 0){}
    ~NewButton(){

    }
    void enterEvent(QEvent *e){
        setStyleSheet("color:rgb(255,255,0);");
    }
    void leaveEvent(QEvent *e){
        setStyleSheet("QPushButton{border:none;background:transparent;color:white;}");
    }

};



#endif // NEWBUTTON_H
