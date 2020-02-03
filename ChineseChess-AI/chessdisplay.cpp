#include "chessdisplay.h"

ChessDisplay::ChessDisplay(CHESSPOS pos,bool is_chess,QString normalImg,QString pressImg, QWidget *parent) : QPushButton (parent), pos(pos) ,is_chess(is_chess),normalImg(normalImg),pressImg(pressImg)
{
    QPixmap pixmap;
    pixmap.load(normalImg);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    this->setIcon(pixmap);
    this->move(10 + pos.x*70, 10 + pos.y*70);

    connect(this,&QPushButton::clicked,[=](){
        emit act(this->pos);
    });
}

void ChessDisplay::displayNormalImg()
{
    QPixmap pixmap;
    pixmap.load(normalImg);
    this->setIcon(pixmap);
    this->move(10 + pos.x*70, 10 + pos.y*70);
}

void ChessDisplay::displayPressImg()
{
    QPixmap pixmap;
    pixmap.load(pressImg);
    this->setIcon(pixmap);
    this->move(10 + pos.x*70, 10 + pos.y*70);

}
