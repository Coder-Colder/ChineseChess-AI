#include "Chess.h"

static int flagBoard 

bool twoKingMeet(CHESSPOS & src, CHESSPOS & tar, int board[10][9])
{

}

bool getRKing(CHESSPOS & pos, int board[10][9])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 3; j < 6; j++)
		{
			if( board[i][j] == 1)
			{
				pos.x = j;
				pos.y = i;
				return true;
			}
		}
	}
	return false;
}
bool getBKing(CHESSPOS & pos, int board[10][9])
{
	for (int i = 7; i < 10; i++)
	{
		for (int j = 3; j < 6; j++)
		{
			if (board[i][j] == 1)
			{
				pos.x = j;
				pos.y = i;
				return true;
			}
		}
	}
	return false;
}

R_King::R_King()
{
	chess_id = 1;
	pos.x = 4;
	pos.y = 0;
}

bool R_King::moveValid(CHESSPOS & tar, int board[10][9])
{
	if (tar.x < 0 || tar.x > 8 || tar.y < 0 || tar.y > 9)
		return false;
	if (tar.x != pos.x + 1 || tar.x != pos.x - 1)
		return false;
	if (tar.y != pos.y + 1 || tar.y != pos.y - 1)
		return false;
	if (is_Red(board[tar.y][tar.x]))
		return false;
	CHESSPOS B_King_Pos;
	getBKing(B_King_Pos);
	if (tar.x == B_King_Pos.x)
	{
		int i;
		for (int i = tar.y + 1; i < B_King_Pos.y)
			if (board[i][tar.x] != 0)
				break;
		if (i == B_King_Pos.y)
			return false;
	}
	return true;
}

void R_King::generateMovement(vector<CHESSPOS>& tar_pos, int board[10][9])
{
	int offset[2] = { 1,-1 };
	CHESSPOS temp;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			temp.x = pos.x + offset[j];
			temp.y = pos.y + offset[i];
			if (!is_Red(board[temp.y][temp.x]) && !is_outRedPalace(board[temp.y][temp.x]))
			{

			}
		}
	}
}


B_King::B_King()
{
	chess_id = 7;
	pos.x = 4;
	pos.y = 9;
}
