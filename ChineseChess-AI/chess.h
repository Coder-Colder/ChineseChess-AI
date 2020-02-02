#ifndef CHESS_H
#define CHESS_H

#include <QWidget>
#include <QPushButton>
#include "define.h"
using namespace std;

class Chess
{
public:
    explicit Chess(CHESSPOS pos, bool exist = true);
    bool exist;//棋子是否存在棋盘上
    CHESSPOS pos;//棋子在棋盘上的位置
    void setPos(CHESSPOS & pos){this->pos = pos;}//设置棋子在棋盘上的位置
    void setExist(){this->exist = true;}//可以直接访问成员或者调用
    void disExist(){this->exist = false;}//可以直接访问成员或者调用
    virtual ~Chess() {}
    virtual bool moveValid(CHESSPOS &tar, char board[10][9]) = 0;					   //确定目标移动位置合法性:针对棋子特定的移动规则
    virtual void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]) = 0; //生成所有的合法的走子位置
signals:

public slots:
};

class R_King : public Chess //红帅
{
public:
    R_King(CHESSPOS pos):Chess(pos) {}
    ~R_King() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};
class B_King : public Chess //黑帅
{
public:
    B_King(CHESSPOS pos):Chess(pos){}
    ~B_King() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class R_Guard : public Chess //红士
{
public:
    R_Guard(CHESSPOS pos):Chess(pos) {}
    ~R_Guard() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class B_Guard : public Chess //黑士
{
public:
    B_Guard(CHESSPOS pos):Chess(pos) {}
    ~B_Guard() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class R_Bishop : public Chess //红象
{
public:
    R_Bishop(CHESSPOS pos):Chess(pos) {}
    ~R_Bishop() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class B_Bishop : public Chess //黑象
{
public:
    B_Bishop(CHESSPOS pos):Chess(pos) {}
    ~B_Bishop() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class R_Pawn : public Chess //红卒
{
public:
    R_Pawn(CHESSPOS pos):Chess(pos) {}
    ~R_Pawn() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class B_Pawn : public Chess //黑卒
{
public:
    B_Pawn(CHESSPOS pos):Chess(pos) {}
    ~B_Pawn() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class R_Horse : public Chess //红马
{
public:
    R_Horse(CHESSPOS pos):Chess(pos) {}
    ~R_Horse() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class B_Horse : public Chess //黑马
{
public:
    B_Horse(CHESSPOS pos):Chess(pos) {}
    ~B_Horse() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class R_Cannon : public Chess //红炮
{
public:
    R_Cannon(CHESSPOS pos):Chess(pos) {}
    ~R_Cannon() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class B_Cannon : public Chess //黑炮
{
public:
    B_Cannon(CHESSPOS pos):Chess(pos) {}
    ~B_Cannon() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class R_Car : public Chess //红车
{
public:
    R_Car(CHESSPOS pos):Chess(pos) {}
    ~R_Car() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

class B_Car : public Chess //黑车
{
public:
    B_Car(CHESSPOS pos):Chess(pos) {}
    ~B_Car() {}
    bool moveValid(CHESSPOS &tar, char board[10][9]);					   //重定义父类函数
    void generateMovement(vector<MOVEMENT> &moveList, char board[10][9]); //重定义父类函数
};

#endif // CHESS_H

