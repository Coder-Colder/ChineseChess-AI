#pragma once
#ifndef HUMAN_H
#define HUMAN_H
#include "define.h"
#include "Board.h"

class Human
{
public:
	Human() {}
	~Human() {}
	MOVEMENT play(Board &board);
};

#endif