#include "gamewidget.h"

static R_King      r_king(CHESSPOS(4, 0));
static R_Guard     r_guard1(CHESSPOS(3, 0));
static R_Guard     r_guard2(CHESSPOS(5, 0));
static R_Bishop    r_bishop1(CHESSPOS(2, 0));
static R_Bishop    r_bishop2(CHESSPOS(6, 0));
static R_Pawn      r_pawn1(CHESSPOS(0, 3));
static R_Pawn      r_pawn2(CHESSPOS(2, 3));
static R_Pawn      r_pawn3(CHESSPOS(4, 3));
static R_Pawn      r_pawn4(CHESSPOS(6, 3));
static R_Pawn      r_pawn5(CHESSPOS(8, 3));
static R_Horse     r_horse1(CHESSPOS(1, 0));
static R_Horse     r_horse2(CHESSPOS(7, 0));
static R_Cannon    r_cannon1(CHESSPOS(1, 2));
static R_Cannon    r_cannon2(CHESSPOS(7, 2));
static R_Car       r_car1(CHESSPOS(0, 0));
static R_Car       r_car2(CHESSPOS(8, 0));
static B_King      b_king(CHESSPOS(4, 9));
static B_Guard     b_guard1(CHESSPOS(3, 9));
static B_Guard     b_guard2(CHESSPOS(5, 9));
static B_Bishop    b_bishop1(CHESSPOS(2, 9));
static B_Bishop    b_bishop2(CHESSPOS(6, 9));
static B_Pawn      b_pawn1(CHESSPOS(0, 6));
static B_Pawn      b_pawn2(CHESSPOS(2, 6));
static B_Pawn      b_pawn3(CHESSPOS(4, 6));
static B_Pawn      b_pawn4(CHESSPOS(6, 6));
static B_Pawn      b_pawn5(CHESSPOS(8, 6));
static B_Horse     b_horse1(CHESSPOS(1, 9));
static B_Horse     b_horse2(CHESSPOS(7, 9));
static B_Cannon    b_cannon1(CHESSPOS(1, 7));
static B_Cannon    b_cannon2(CHESSPOS(7, 7));
static B_Car       b_car1(CHESSPOS(0, 9));
static B_Car       b_car2(CHESSPOS(8, 9));

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
    initChessDisplay(board.board);

    //初始化窗口信息
    setWindowIcon(QIcon("://res/B_BISHOP1.png"));
    setWindowTitle("中国象棋");
    setFixedSize(650,720);

    Red = new GammaGo_v2(20000,RED);
    Black = new Human(BLACK);
    this->mode = HvsM;
    state = WAIT;

    MOVEMENT mvmt;
    //红先走
    Red->play(board,mvmt);
    board.moveNext(mvmt);
    this->moveNextDisplay(mvmt);

    for(int i = 0;i < 10;i++)
    {
        for(int j = 0;j < 9;j++)
        {
               connect(chessDisplay[i][j],&ChessDisplay::act,this,&GameWidget::humanPlay);
        }
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    //绘制设置背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Board.JPG");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void GameWidget::initChessDisplay(char board[10][9])
{
    for(int i = 0;i < 10;i++)
    {
        for(int j = 0;j < 9;j++)
        {
            switch (board[i][j])
            {
            case R_KING:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/R_KING1.png",":/res/R_KING2.png",this);
                break;
            case R_GUARD1:
            case R_GUARD2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/R_GUARD1.png",":/res/R_GUARD2.png",this);
                break;
            case R_BISHOP1:
            case R_BISHOP2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/R_BISHOP1.png",":/res/R_BISHOP2.png",this);
                break;
            case R_PAWN1:
            case R_PAWN2:
            case R_PAWN3:
            case R_PAWN4:
            case R_PAWN5:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/R_PAWN1.png",":/res/R_PAWN2.png",this);
                break;
            case R_HORSE1:
            case R_HORSE2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/R_HORSE1.png",":/res/R_HORSE2.png",this);
                break;
            case R_CANNON1:
            case R_CANNON2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/R_CANNON1.png",":/res/R_CANNON2.png",this);
                break;
            case R_CAR1:
            case R_CAR2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/R_CAR1.png",":/res/R_CAR2.png",this);
                break;
            case B_KING:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/B_KING1.png",":/res/B_KING2.png",this);
                break;
            case B_GUARD1:
            case B_GUARD2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/B_GUARD1.png",":/res/B_GUARD2.png",this);
                break;
            case B_BISHOP1:
            case B_BISHOP2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/B_BISHOP1.png",":/res/B_BISHOP2.png",this);
                break;
            case B_PAWN1:
            case B_PAWN2:
            case B_PAWN3:
            case B_PAWN4:
            case B_PAWN5:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/B_PAWN1.png",":/res/B_PAWN2.png",this);
                break;
            case B_HORSE1:
            case B_HORSE2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/B_HORSE1.png",":/res/B_HORSE2.png",this);
                break;
            case B_CANNON1:
            case B_CANNON2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/B_CANNON1.png",":/res/B_CANNON2.png",this);
                break;
            case B_CAR1:
            case B_CAR2:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),true,":/res/B_CAR1.png",":/res/B_CAR2.png",this);
                break;
            default:
                chessDisplay[i][j] = new ChessDisplay(CHESSPOS(j,i),false,":/res/White1.png",":/res/White2.png",this);
            }
        }
    }
}

GameWidget::~GameWidget()
{
    delete Red;
    delete Black;
}

void GameWidget::moveNextDisplay(MOVEMENT & move)
{
    if(chessDisplay[move.tar.y][move.tar.x]->is_chess)
    {
        //交换两个指针
        ChessDisplay * temp = chessDisplay[move.tar.y][move.tar.x];
        chessDisplay[move.tar.y][move.tar.x] = chessDisplay[move.src.y][move.src.x];
        chessDisplay[move.src.y][move.src.x] = temp;
        //将src改为空白
        chessDisplay[move.src.y][move.src.x]->is_chess = false;
        chessDisplay[move.src.y][move.src.x]->normalImg = ":/res/White1.png";
        chessDisplay[move.src.y][move.src.x]->pressImg = ":/res/White2.png";
        //交换位置
        chessDisplay[move.src.y][move.src.x]->pos = move.src;
        chessDisplay[move.tar.y][move.tar.x]->pos = move.tar;
        //显示
        chessDisplay[move.src.y][move.src.x]->displayNormalImg();
        chessDisplay[move.tar.y][move.tar.x]->displayNormalImg();

    }
    else {
        ChessDisplay * temp = chessDisplay[move.tar.y][move.tar.x];
        chessDisplay[move.tar.y][move.tar.x] = chessDisplay[move.src.y][move.src.x];
        chessDisplay[move.src.y][move.src.x] = temp;

        chessDisplay[move.src.y][move.src.x]->pos = move.src;
        chessDisplay[move.tar.y][move.tar.x]->pos = move.tar;

        chessDisplay[move.src.y][move.src.x]->displayNormalImg();
        chessDisplay[move.tar.y][move.tar.x]->displayNormalImg();
    }

}

void GameWidget::humanPlay(CHESSPOS pos)
{
    switch (state)
    {
    case WAIT :
        if(chessDisplay[pos.y][pos.x]->is_chess)
        {
            chessDisplay[pos.y][pos.x]->displayPressImg();
            state = PRESS_CHESS;
            lastPress = pos;
        }
        else {
            chessDisplay[pos.y][pos.x]->displayPressImg();
            lastPress = pos;
            state = PRESS_BOARD;
        }
        break;
    case PRESS_CHESS:;
        if(chess[int(board.board[lastPress.y][lastPress.x])]->moveValid(pos,board.board))
        {
            MOVEMENT mvmt;
            mvmt.src = lastPress;
            mvmt.tar = pos;
            moveNextDisplay(mvmt);
            state = WAIT;
            countiuePlay(mvmt);
        }
        else {
            chessDisplay[lastPress.y][lastPress.x]->displayNormalImg();
            state = WAIT;
        }
        break;
    case PRESS_BOARD:
        if(chessDisplay[pos.y][pos.x]->is_chess)
        {
            chessDisplay[lastPress.y][lastPress.x]->displayNormalImg();
            chessDisplay[pos.y][pos.x]->displayPressImg();
            state = PRESS_CHESS;
            lastPress = pos;
        }
        else {
            chessDisplay[lastPress.y][lastPress.x]->displayNormalImg();
            chessDisplay[pos.y][pos.x]->displayPressImg();
            state = PRESS_BOARD;
            lastPress = pos;
        }
        break;
    default:
        assert(0);

    }
}

void GameWidget::gameOverCheck()
{
    if(chess[B_KING]->exist == false)
        gameOverLose();
    else if(chess[R_KING]->exist == false)
        gameOverWin();
}

void GameWidget::countiuePlay(MOVEMENT & move)
{
    board.moveNext(move);
    gameOverCheck();
    Red->play(board,move);
    board.moveNext(move);
    moveNextDisplay(move);
    gameOverCheck();
}

void GameWidget::gameOverWin()
{

}

void GameWidget::gameOverLose()
{

}
