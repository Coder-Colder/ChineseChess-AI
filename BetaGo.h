#pragma once
#ifndef BETAGO_H
#define BETAGO_H

#include "Player.h"



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