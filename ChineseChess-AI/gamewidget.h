#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include "define.h"
#include "player.h"
#include "chess.h"
#include "human.h"
#include "chessdisplay.h"
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    void paintEvent(QPaintEvent *);
    void initChessDisply(char board[10][9]);
    unsigned char over_flag;
    int mode;
    Player * Red;
    Player * Black;
    Board board;

    ChessDisplay * chessDisply[10][9];
signals:

public slots:
};

#endif // GAMEWIDGET_H
