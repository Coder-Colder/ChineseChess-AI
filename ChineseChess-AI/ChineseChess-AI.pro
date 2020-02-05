#-------------------------------------------------
#
# Project created by QtCreator 2020-01-30T12:29:42
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChineseChess-AI
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
        mainwidget.cpp \
    choosewidget.cpp \
    gamewidget.cpp \
    chess.cpp \
    chessdisplay.cpp \
    board.cpp \
    human.cpp \
    GammaGo_v2.cpp \
    overwidget.cpp

HEADERS += \
        mainwidget.h \
    choosewidget.h \
    gamewidget.h \
    chess.h \
    define.h \
    chessdisplay.h \
    player.h \
    human.h \
    board.h \
    GammaGo_v2.h \
    overwidget.h

FORMS += \
        mainwidget.ui \
    overwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
