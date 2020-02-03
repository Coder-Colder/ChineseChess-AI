﻿#pragma once
#ifndef BOARD_H
#define BOARD_H
#include "chess.h"
#include "define.h"

extern Chess * chess[32];

class Board//记录棋局形势
{
public:
	char board[10][9];
	void moveNext(MOVEMENT & move);//根据走子方法更新棋面
	Board();
	~Board() {}
};
#endif
