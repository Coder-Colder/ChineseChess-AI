#include "gamewidget.h"

R_King      r_king(CHESSPOS(4, 0));
R_Guard     r_guard1(CHESSPOS(3, 0));
R_Guard     r_guard2(CHESSPOS(5, 0));
R_Bishop    r_bishop1(CHESSPOS(2, 0));
R_Bishop    r_bishop2(CHESSPOS(6, 0));
R_Pawn      r_pawn1(CHESSPOS(0, 3));
R_Pawn      r_pawn2(CHESSPOS(2, 3));
R_Pawn      r_pawn3(CHESSPOS(4, 3));
R_Pawn      r_pawn4(CHESSPOS(6, 3));
R_Pawn      r_pawn5(CHESSPOS(8, 3));
R_Horse     r_horse1(CHESSPOS(1, 0));
R_Horse     r_horse2(CHESSPOS(7, 0));
R_Cannon    r_cannon1(CHESSPOS(1, 2));
R_Cannon    r_cannon2(CHESSPOS(7, 2));
R_Car       r_car1(CHESSPOS(0, 0));
R_Car       r_car2(CHESSPOS(8, 0));
B_King      b_king(CHESSPOS(4, 9));
B_Guard     b_guard1(CHESSPOS(3, 9));
B_Guard     b_guard2(CHESSPOS(5, 9));
B_Bishop    b_bishop1(CHESSPOS(2, 9));
B_Bishop    b_bishop2(CHESSPOS(6, 9));
B_Pawn      b_pawn1(CHESSPOS(0, 6));
B_Pawn      b_pawn2(CHESSPOS(2, 6));
B_Pawn      b_pawn3(CHESSPOS(4, 6));
B_Pawn      b_pawn4(CHESSPOS(6, 6));
B_Pawn      b_pawn5(CHESSPOS(8, 6));
B_Horse     b_horse1(CHESSPOS(1, 9));
B_Horse     b_horse2(CHESSPOS(7, 9));
B_Cannon    b_cannon1(CHESSPOS(1, 7));
B_Cannon    b_cannon2(CHESSPOS(7, 7));
B_Car       b_car1(CHESSPOS(0, 9));
B_Car       b_car2(CHESSPOS(8, 9));

Chess * chess[32] ={
    &r_king,
    &r_guard1,
    &r_guard2,
    &r_bishop1,
    &r_bishop2,
    &r_pawn1,
    &r_pawn2,
    &r_pawn3,
    &r_pawn4,
    &r_pawn5,
    &r_horse1,
    &r_horse2,
    &r_cannon1,
    &r_cannon2,
    &r_car1,
    &r_car2,
    &b_king,
    &b_guard1,
    &b_guard2,
    &b_bishop1,
    &b_bishop2,
    &b_pawn1,
    &b_pawn2,
    &b_pawn3,
    &b_pawn4,
    &b_pawn5,
    &b_horse1,
    &b_horse2,
    &b_cannon1,
    &b_cannon2,
    &b_car1,
    &b_car2,
};
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    initChessDisply(board.board);

    //初始化窗口信息
    setWindowIcon(QIcon("://res/B_BISHOP1.png"));
    setWindowTitle("中国象棋");
    setFixedSize(650,720);
}

void GameWidget::paintEvent(QPaintEvent *)
{
    //绘制设置背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Board.JPG");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void GameWidget::initChessDisply(char board[10][9])
{
    for(int i = 0;i < 10;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            switch (board[i][j])
            {
            case R_KING:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/R_KING1.png",":/res/R_KING2.png",this);
                break;
            case R_GUARD1:
            case R_GUARD2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/R_GUARD1.png",":/res/R_GUARD2.png",this);
                break;
            case R_BISHOP1:
            case R_BISHOP2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/R_BISHOP1.png",":/res/R_BISHOP2.png",this);
                break;
            case R_PAWN1:
            case R_PAWN2:
            case R_PAWN3:
            case R_PAWN4:
            case R_PAWN5:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/R_PAWN1.png",":/res/R_PAWN2.png",this);
                break;
            case R_HORSE1:
            case R_HORSE2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/R_HORSE1.png",":/res/R_HORSE2.png",this);
                break;
            case R_CANNON1:
            case R_CANNON2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/R_CANNON1.png",":/res/R_CANNON2.png",this);
                break;
            case R_CAR1:
            case R_CAR2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/R_CAR1.png",":/res/R_CAR2.png",this);
                break;
            case B_KING:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/B_KING1.png",":/res/B_KING2.png",this);
                break;
            case B_GUARD1:
            case B_GUARD2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/B_GUARD1.png",":/res/B_GUARD2.png",this);
                break;
            case B_BISHOP1:
            case B_BISHOP2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/B_BISHOP1.png",":/res/B_BISHOP2.png",this);
                break;
            case B_PAWN1:
            case B_PAWN2:
            case B_PAWN3:
            case B_PAWN4:
            case B_PAWN5:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/B_PAWN1.png",":/res/B_PAWN2.png",this);
                break;
            case B_HORSE1:
            case B_HORSE2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/B_HORSE1.png",":/res/B_HORSE2.png",this);
                break;
            case B_CANNON1:
            case B_CANNON2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/B_CANNON1.png",":/res/B_CANNON2.png",this);
                break;
            case B_CAR1:
            case B_CAR2:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/B_CAR1.png",":/res/B_CAR2.png",this);
                break;
            default:
                chessDisply[j][i] = new ChessDisplay(CHESSPOS(j,i),":/res/White1.png",":/res/White2.png",this);
            }
        }
    }
}

GameWidget::~GameWidget()
{
    delete Red;
    delete Black;
}
