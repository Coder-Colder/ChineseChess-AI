#pragma once
#ifndef GAME_H
#define GAME_H

#include "BetaGo.h"
#include "Human.h"
#include "Board.h"

/*mode*/
#define MvsM 0 // 机器对机器
#define HvsM 1 // 人对机器
#define HvsH 2 // 人对人

/*side / over_flag*/
#define GMAEON 0
#define RED 1
#define BLACK 2

class Game//游戏运行主逻辑
{
	Board board;
    int over_flag;
public:
	Game() {over_flag = GMAEON;}
	~Game() {}
	int gameStart(int mode);//返回赢棋的一方
    void gameOverCheck(int side);//在side方走子后判断棋局是否结束
};
#endif // !GAME_H