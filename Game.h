#pragma once
#ifndef GAME_H
#define GAME_H

#include "BetaGo.h"
#include "Board.h"
class Game//游戏运行主逻辑
{
	Board board;
public:
	Game();
	~Game();
	void gameStart();
};
#endif // !GAME_H