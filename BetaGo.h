#pragma once
#ifndef BETAGO_H
#define BETAGO_H

#include "define.h"
#include "Board.h"

class BetaGo
{
public:
	BetaGo() {}
	~BetaGo() {}
	void play(Board &board, MOVEMENT &mvmt);
	int evaluate(Board &board);
};
#endif // !BETAGO_H