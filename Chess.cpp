#include "Chess.h"

bool getRKing(CHESSPOS & pos, int board[10][9])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 3; j < 6; j++)
		{
			if( board[i][j] == R_KING)
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
			if (board[i][j] == B_KING)
			{
				pos.x = j;
				pos.y = i;
				return true;
			}
		}
	}
	return false;
}



