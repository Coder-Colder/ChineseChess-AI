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
    explicit ChessDisplay(CHESSPOS pos, QString normalImg,QString pressImg, QWidget *parent = nullptr);
    CHESSPOS pos;//在棋盘上的位置
    QString normalImg;
    QString pressImg;
signals:

public slots:
};

#endif // CHESSDISPLAY_H
