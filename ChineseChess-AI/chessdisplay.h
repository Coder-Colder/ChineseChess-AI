#ifndef CHESSDISPLAY_H
#define CHESSDISPLAY_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QString>
#include "define.h"

class ChessDisplay : public QPushButton
{
    Q_OBJECT
public:
    explicit ChessDisplay(CHESSPOS pos, bool is_chess, QString normalImg,QString pressImg, QWidget *parent = nullptr);
    CHESSPOS pos;//在棋盘上的位置
    bool is_chess;//是否为棋子
    QString normalImg;
    QString pressImg;
    void displayNormalImg();
    void displayPressImg();
signals:
    void act(CHESSPOS);
public slots:
};

#endif // CHESSDISPLAY_H
