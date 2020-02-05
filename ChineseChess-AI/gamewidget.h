#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QSound>
#include "define.h"
#include "player.h"
#include "chess.h"
#include "human.h"
#include "chessdisplay.h"
#include "GammaGo_v2.h"
#include "overwidget.h"


/*mode*/
#define MvsM 0 // 机器对机器
#define HvsM 1 // 人对机器
#define HvsH 2 // 人对人


class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    void paintEvent(QPaintEvent *);
    void initChessDisplay(char board[10][9]);
    void moveNextDisplay(MOVEMENT & move);
    void countiuePlay(MOVEMENT & move);
    void gameOverWin();
    void gameOverLose();
    int mode;
    Player * Red;
    Player * Black;
    Board board;

    int state;//标记人类当前状态
    CHESSPOS lastPress;//记录上次按下的按键
    ChessDisplay * chessDisplay[10][9];

    //需要的声音
    QSound *clickSound;
    QSound *moveSound;
    QSound *captrueSound;
    QSound *illegalSound;
    QSound *startSound;
    QSound *winSound;
    QSound *loseSound;

signals:
    void win();
    void lose();
public slots:
    void humanPlay(CHESSPOS pos);
};

#endif // GAMEWIDGET_H
