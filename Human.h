#pragma once
#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"

class Human:public Player
{
public:
	Human(unsigned char side = RED):Player(side) {}
	virtual ~Human() {}
	virtual void play(Board &board, MOVEMENT &mvmt);
};

#endif