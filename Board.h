#pragma once
#ifndef BOARD_H
#define BOARD_H
#include "Chess.h"
#include "define.h"

class Board//记录棋局形势
{
public:
	Chess* chess[32];//记录
	int board[10][9];
	void display();//打印棋盘
	void moveNext(MOVEMENT & move);//根据走子方法更新棋面
	bool getRKing(CHESSPOS & pos);//获取红帅
	bool getBKing(CHESSPOS & pos);//获取黑帅
	Board();
	~Board() {}
};
#endif
