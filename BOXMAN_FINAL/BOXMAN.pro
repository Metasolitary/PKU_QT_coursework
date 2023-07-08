#-------------------------------------------------
#
# Project created by QtCreator 2023-06-01T14:41:01
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
CONFIG   += resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BOXMAN
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        BasicLand.cpp \
        Box.cpp \
        Floor.cpp \
        GameInfo.cpp \
        Person.cpp \
        Vacuum.cpp \
        Wall.cpp \
        Map.cpp \
        Destination.cpp \
        FakeWall.cpp \
        Portal.cpp \
        game1.cpp \
        mainwindow.cpp \
        newbutton.cpp \
        widget.cpp \
    game2.cpp \
    game3.cpp \
    game4.cpp \
 game5.cpp \
game6.cpp \
game7.cpp \
game8.cpp \


HEADERS += \
        BasicLand.h \
        Box.h \
        Floor.h \
        GameInfo.h \
        Map.h \
        Person.h \
        Vacuum.h \
        Wall.h \
        GameObject.h \
        Destination.h \
        FakeWall.h \
        Portal.h \
        game1.h \
        mainwindow.h \
        newbutton.h \
        widget.h \
    game2.h \
    game3.h \
    game4.h \
game5.h \
game6.h \
game7.h \
game8.h \



FORMS += \
        game1.ui \
        mainwindow.ui \
        widget.ui \
    game2.ui \
    game3.ui \
    game4.ui \
game5.ui \
game6.ui \
game7.ui \
game8.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    C:/Users/蝉冰子/Downloads/Gymnopédie no. 1 (for Harp).mp3
