#pragma once
#ifndef BETAGO_H
#define BETAGO_H

#include "Player.h"

//定义每种棋子的价值
#define BASEVELUE_PAWN 100
#define BASEVELUE_GUARD 250
#define BASEVELUE_BISHOP 250
#define BASEVELUE_CAR 500
#define BASEVELUE_HORSE 350
#define BASEVELUE_CANNON 350
#define BASEVELUE_KING 10000
//定义棋子灵活性
#define FLEXIBILITY_PAWN 15
#define FLEXIBILITY_GUARD 1
#define FLEXIBILITY_BISHOP 1
#define FLEXIBILITY_CAR 6
#define FLEXIBILITY_HORSE 12
#define FLEXIBILITY_CANNON 6
#define FLEXIBILITY_KING 0

class BetaGo:public Player
{
public:
	BetaGo(unsigned char side = RED):Player(side) {}
	~BetaGo() {}
	void play(Board &board, MOVEMENT &mvmt);
private:
	int evaluate(Board &board);
};
#endif // !BETAGO_H