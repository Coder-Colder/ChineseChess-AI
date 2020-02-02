#include "chessdisplay.h"

ChessDisplay::ChessDisplay(CHESSPOS pos,QString normalImg,QString pressImg, QWidget *parent) : QPushButton (parent) ,pos(pos) ,normalImg(normalImg),pressImg(pressImg)
{
    QPixmap pixmap;
    pixmap.load(normalImg);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    this->setIcon(pixmap);
    this->move(10 + pos.x*70, 10 + pos.y*70);
}
