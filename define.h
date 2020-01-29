#pragma once
#ifndef DEFINE_H
#define DEFINE_H

struct CHESSPOS//棋子位置
{
	int x;
	int y;
public:
	CHESSPOS(int x = 0, int y = 0):x(x), y(y) { }
	CHESSPOS(const CHESSPOS & pos):x(pos.x), y(pos.y) { }
	CHESSPOS & operator = (const CHESSPOS & pos ){ this->x = pos.x; this->y = pos.y; }
};

struct MOVEMENT//走子描述
{
	CHESSPOS src;
	CHESSPOS tar;
public:
	MOVEMENT(CHESSPOS src = CHESSPOS(), CHESSPOS tar = CHESSPOS()):src(src), tar(tar) { }
	MOVEMENT(const MOVEMENT & mvmt):src(mvmt.src), tar(mvmt.tar) { }
	MOVEMENT & operator = (const MOVEMENT & mvmt) { this->src = mvmt.src; this->tar = mvmt.tar; }
};


/*chess id*/
#define R_KING 		0 
#define R_GUARD1	1 
#define R_GUARD2 	2 
#define R_BISHOP1 	3 
#define R_BISHOP2 	4 
#define R_PAWN1 	5 
#define R_PAWN2 	6 
#define R_PAWN3 	7 
#define R_PAWN4 	8 
#define R_PAWN5 	9 
#define R_HORSE1 	10
#define R_HORSE2 	11
#define R_CANNON1 	12
#define R_CANNON2 	13
#define R_CAR1 		14
#define R_CAR2 		15

#define B_KING 		16
#define B_GUARD1 	17
#define B_GUARD2 	18
#define B_BISHOP1 	19
#define B_BISHOP2 	20
#define B_PAWN1 	21
#define B_PAWN2 	22
#define B_PAWN3 	23
#define B_PAWN4	 	24
#define B_PAWN5 	25
#define B_HORSE1 	26
#define B_HORSE2 	27
#define B_CANNON1 	28
#define B_CANNON2 	29
#define B_CAR1 		30
#define B_CAR2 		31
#define NoChess 	32 

#define is_Red(CHESSID) CHESSID <= 15 && CHESSID >= 0
#define is_Black(CHESSID) CHESSID <= 31 && CHESSID >= 16


#define OUTBOARD 0
#define INBOARD 1
#define RSQUARE 2
#define BSQUARE 3

extern int flagBoard[14][13];

#define is_outBoard(FLAG) FLAG == OUTBOARD
#define is_outRedPalace(FLAG) FLAG == RSQUARE
#define is_outBlackPalace(FLAG) FLAG == BSQUARE

#endif