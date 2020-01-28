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
	virtual void setPos(CHESSPOS &tar) = 0;//棋子移动,设置下一个位置坐标
	virtual bool moveValid(CHESSPOS &tar) = 0;//确定目标移动位置合法性:针对棋子特定的移动规则
	virtual void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]) = 0;//生成所有的合法的走子位置
};

class R_King :public Chess//红帅
{
public:
	R_King();
	~R_King();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};
class B_King :public Chess//黑帅
{
public:
	B_King();
	~B_King();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};

class R_Guard :public Chess//红士
{
public:
	R_Guard();
	~R_Guard();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};

class B_Guard :public Chess//黑士
{
public:
	B_Guard();
	~B_Guard();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};

class R_Bishop :public Chess//红象
{
public:
	R_Bishop();
	~R_Bishop();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};

class B_Bishop :public Chess//黑象
{
public:
	B_Bishop();
	~B_Bishop();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};

class R_Pawn :public Chess//红卒
{
public:
	R_Pawn();
	~R_Pawn();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};

class B_Pawn :public Chess//黑卒
{
public:
	B_Pawn();
	~B_Pawn();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};

class horse :public Chess//马：不区分红黑
{
public:
	horse();
	~horse();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};

class Cannon :public Chess//炮：不区分红黑
{
public:
	Cannon();
	~Cannon();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};

class Car :public Chess//车：不区分红黑
{
public:
	Car();
	~Car();
	void setPos(CHESSPOS &tar);//重定义父类函数
	bool moveValid(CHESSPOS &tar);//重定义父类函数
	void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]);//重定义父类函数
};


#endif // !CHESS_H
