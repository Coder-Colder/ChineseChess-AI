#pragma once
#ifndef CHESS_H
#define CHESS_H
#include "define.h"
#include <vector>
using namespace std;
class Chess//记录棋子在棋盘上的坐标；根据形势给出所有合法走子；检验所给走子方法的合法性
{
public:
	Chess() {}
	~Chess() {}
	int chess_id;//棋子编号
	CHESSPOS pos;//棋子在棋盘上的位置
	void setPos(CHESSPOS &tar) { pos = tar; }//棋子移动,设置下一个位置坐标
	virtual bool moveValid(CHESSPOS &tar, int board[10][9]) = 0;//确定目标移动位置合法性:针对棋子特定的移动规则
	virtual void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]) = 0;//生成所有的合法的走子位置
};

class R_King :public Chess//红帅
{
public:
	R_King();
	~R_King();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};
class B_King :public Chess//黑帅
{
public:
	B_King();
	~B_King();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class R_Guard :public Chess//红士
{
public:
	R_Guard();
	~R_Guard();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class B_Guard :public Chess//黑士
{
public:
	B_Guard();
	~B_Guard();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class R_Bishop :public Chess//红象
{
public:
	R_Bishop();
	~R_Bishop();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class B_Bishop :public Chess//黑象
{
public:
	B_Bishop();
	~B_Bishop();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class R_Pawn :public Chess//红卒
{
public:
	R_Pawn();
	~R_Pawn();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class B_Pawn :public Chess//黑卒
{
public:
	B_Pawn();
	~B_Pawn();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class R_Horse :public Chess//红马
{
public:
	R_Horse();
	~R_Horse();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class B_Horse :public Chess//黑马
{
public:
	B_Horse();
	~B_Horse();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class R_Cannon :public Chess//红炮
{
public:
	R_Cannon();
	~R_Cannon();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class B_Cannon :public Chess//黑炮
{
public:
	B_Cannon();
	~B_Cannon();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class R_Car :public Chess//红车
{
public:
	R_Car();
	~R_Car();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

class B_Car :public Chess//黑车
{
public:
	B_Car();
	~B_Car();
	bool moveValid(CHESSPOS &tar, int board[10][9]);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[10][9]);//重定义父类函数
};

#endif // !CHESS_H
