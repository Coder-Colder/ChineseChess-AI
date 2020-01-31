#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "BetaGo.h"
#include "GammaGo.h"
#include "GammaGo_v2.h"
#include "Human.h"
#include "Board.h"

/*mode*/
#define MvsM 0 // 机器对机器
#define HvsM 1 // 人对机器
#define HvsH 2 // 人对人

class Game//游戏运行主逻辑
{
    unsigned char over_flag;
	int mode;
	Player * Red;
	Player * Black;
	Board board;
public:
	Game(int mode = HvsM);
	~Game() {delete Red; delete Black;}
	int Start();//返回赢棋的一方
private:
    void gameOverCheck(int side);//在side方走子后判断棋局是否结束
};

#endif // !GAME_H