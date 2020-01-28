#pragma once
#ifndef DEFINE_H
#define DEFINE_H

struct CHESSPOS//棋子位置
{
	int x;
	int y;
};

struct MOVEMENT//走子描述
{
	CHESSPOS src;
	CHESSPOS tar;
};

/*chess id*/
#define NoChess 0
#define R_KING 1
#define R_GUARD 2
#define R_BISHOP 3
#define R_PAWN 4
#define R_HORSE 5
#define R_CANNON 6
#define R_CAR 7

#define B_KING 8
#define B_GUARD 9
#define B_BISHOP 10
#define B_PAWN 11
#define B_HORSE 12
#define B_CANNON 13
#define B_CAR 14

#define is_Red(CHESSID) CHESSID <= 7 && CHESSID >= 1
#define is_Black(CHESSID) CHESSID <= 14 && CHESSID >= 8

#endif