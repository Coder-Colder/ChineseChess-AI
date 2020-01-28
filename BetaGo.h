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
	MOVEMENT play(Board &board);
	int evaluate(Board &board);
};
#endif // !BETAGO_H
