#pragma once
#ifndef CHESS_H
#define CHESS_H
#include "define.h"
#include <vector>
using namespace std;
class Chess//记录棋子在棋盘上的坐标；根据形势给出所有合法走子；检验所给走子方法的合法性
{
public:
	Chess();
	~Chess();
	int chess_id;//棋子编号
	CHESSPOS pos;//棋子在棋盘上的位置
	virtual void setPos(CHESSPOS &tar) = 0;//棋子移动,设置下一个位置坐标
	virtual bool moveValid(CHESSPOS &tar) = 0;//确定目标移动位置合法性:针对棋子特定的移动规则
	virtual void generateMovement(vector<CHESSPOS> &tar_pos, int board[9][10]) = 0;//生成所有的合法的走子位置
};

#endif // !CHESS_H
