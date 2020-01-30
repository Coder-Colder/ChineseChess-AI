#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include"Board.h"
#include"define.h"

/*side*/
#define RED 0
#define BLACK 1

class Player
{
protected:
    unsigned char side;//玩家阵营
public:
    Player(unsigned char side = RED):side(side){}
    virtual ~Player(){}
    virtual void play(Board &board, MOVEMENT &mvmt) = 0;
};

#endif