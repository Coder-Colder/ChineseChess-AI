#include "Chess.h"
#include <vector>
bool twoKingMeet(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	CHESSPOS R_King_Pos;
	getRKing(R_King_Pos, board);
	CHESSPOS B_King_Pos;
	getBKing(B_King_Pos, board);
	//先检查两王是否在一条线上，在检查当前棋子是否在两王之间
	if (R_King_Pos.x == B_King_Pos.x && R_King_Pos.x == cur.x && cur.x != tar.x && cur.y > R_King_Pos.y && cur.y < B_King_Pos.y)
	{
		//确定当前棋子是两王之间唯一的棋子
		for (int i = cur.y; i < B_King_Pos.y, i++)
		{
			if (board[i][cur.x] != 0)
				return false;
		}
		for (int i = cur.y; i > R_King_Pos.y, i--)
		{
			if (board[i][cur.x] != 0)
				return false;
		}
		return true;
	}
	return false;
}

bool getRKing(CHESSPOS &pos, int board[10][9])
{
	for (int i = 0; i < 3; i++)
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
bool getBKing(CHESSPOS &pos, int board[10][9])
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

bool R_King::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(flagBoard[tar.y][tar.x]))
		return false;
	if ((tar.x != cur.x + 1 || tar.x != cur.x - 1) && tar.y == cur.y)
		return false;
	if ((tar.y != cur.y + 1 || tar.y != cur.y - 1) && tar.x == cur.x)
		return false;
	if (is_Red(board[tar.y][tar.x]))
		return false;
	CHESSPOS B_King_Pos;
	getBKing(B_King_Pos, board);
	if (tar.x == B_King_Pos.x)
	{
		int i;
		for (int i = tar.y + 1; i < B_King_Pos.y; i++)
			if (board[i][tar.x] != 0)
				break;
		if (i == B_King_Pos.y)
			return false;
	}
	return true;
}

void R_King::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
	int offset[2] = {1, -1};
	CHESSPOS temp;
	for (int i = 0; i < 2; i++)
	{
		temp.x = cur.x;
		temp.y = cur.y + offset[i];
		if (!is_Red(board[temp.y][temp.x]) && !is_outRedPalace(temp.y, temp.x))
		{
			tar_pos.push_back(temp);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		temp.x = cur.x + offset[i];
		temp.y = cur.y;
		if (!is_Red(board[temp.y][temp.x]) && !is_outRedPalace(temp.y, temp.x))
		{
			tar_pos.push_back(temp);
		}
	}
}

bool B_King::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(flagBoard[tar.y][tar.x]))
		return false;
	if ((tar.x != cur.x + 1 || tar.x != cur.x - 1) && tar.y == cur.y)
		return false;
	if ((tar.y != cur.y + 1 || tar.y != cur.y - 1) && tar.x == cur.x)
		return false;
	if (is_Black(board[tar.y][tar.x]))
		return false;
	CHESSPOS R_King_Pos;
	getRKing(R_King_Pos, board);
	if (tar.x == R_King_Pos.x)
	{
		int i;
		for (int i = tar.y - 1; i > R_King_Pos.y; i--)
			if (board[i][tar.x] != 0)
				break;
		if (i == R_King_Pos.y)
			return false;
	}
	return true;
}

void B_King::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
	int offset[2] = {1, -1};
	CHESSPOS temp;
	for (int i = 0; i < 2; i++)
	{
		temp.x = cur.x;
		temp.y = cur.y + offset[i];
		if (!is_Black(board[temp.y][temp.x]) && !is_outBlackPalace(temp.y, temp.x))
		{
			tar_pos.push_back(temp);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		temp.x = cur.x + offset[i];
		temp.y = cur.y;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBlackPalace(temp.y, temp.x))
		{
			tar_pos.push_back(temp);
		}
	}
}

bool R_Guard::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	if (cur.y == 1 && cur.x == 4)
	{
		int offset_x[2] = {3, 5};
		int offset_y[2] = {0, 2};
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (tar.x == offset_x[i] && tar.y == offset_y[j] && !is_Red(board[tar.y][tar.x]) && !twoKingMeet(cur, tar, board))
					return true;
			}
		}
	}
	else
	{
		if (tar.x == 4 && tar.y == 1 && !is_Red(board[1][4]) && !twoKingMeet(cur, tar, board))
			return true;
	}
	return false;
}

void R_Guard::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	if (cur.y == 1 && cur.x == 4)
	{
		int offset_x[2] = {3, 5};
		int offset_y[2] = {0, 2};
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				temp.x = offset_x[i];
				temp.y = offset_y[i];
				if (!is_Red(board[temp.y][temp.x]))
				{
					tar_pos.push_back(temp);
				}
			}
		}
	}
	else
	{
		temp.x = 4;
		temp.y = 1;
		if (!is_Red(board[1][4]))
			tar_pos.push_back(temp);
	}
}

bool B_Guard::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	if (cur.y == 8 && cur.x == 4)
	{
		int offset_x[2] = {3, 5};
		int offset_y[2] = {7, 9};
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (tar.x == offset_x[i] && tar.y == offset_y[j] && !is_Black(board[tar.y][tar.x]) && !twoKingMeet(cur, tar, board))
					return true;
			}
		}
	}
	else
	{
		if (tar.x == 4 && tar.y == 8 && !is_Black(board[8][4]) && !twoKingMeet(cur, tar, board))
			return true;
	}
	return false;
}

void B_Guard::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	if (cur.y == 1 && cur.x == 4)
	{
		int offset_x[2] = {3, 5};
		int offset_y[2] = {7, 9};
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				temp.x = offset_x[i];
				temp.y = offset_y[i];
				if (!is_Black(board[temp.y][temp.x]))
				{
					tar_pos.push_back(temp);
				}
			}
		}
	}
	else
	{
		temp.x = 4;
		temp.y = 8;
		if (!is_Red(board[8][4]))
			tar_pos.push_back(temp);
	}
}

bool R_Bishop::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	int offset_eye[2] = {1, -1};
	int offset[2] = {2, -2};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int eye_x = cur.x + offset_eye[j];
			int eye_y = cur.y + offset_eye[i];
			if (tar.x == cur.x + offset[j] && tar.y == cur.y + offset[i] && !is_Red(board[tar.y][tar.x]) && board[eye_y][eye_x] == NoChess)
			{
				return true;
			}
		}
	}
	return false;
}

void R_Bishop::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	int offset_eye[2] = {1, -1};
	int offset[2] = {2, -2};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			temp.x = cur.x + offset[j];
			temp.y = cur.y + offset[i];
			int eye_x = cur.x + offset_eye[j];
			int eye_y = cur.y + offset_eye[i];
			if (!is_outBoard(temp.y, temp.x) && !is_Red(board[temp.y][temp.x]) && board[eye_y][eye_x] == NoChess)
				tar_pos.push_back(temp);
		}
	}
}

bool B_Bishop::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	int offset_eye[2] = {1, -1};
	int offset[2] = {2, -2};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int eye_x = cur.x + offset_eye[j];
			int eye_y = cur.y + offset_eye[i];
			if (tar.x == cur.x + offset[j] && tar.y == cur.y + offset[i] && !is_Black(board[tar.y][tar.x]) && board[eye_y][eye_x] == NoChess)
			{
				return true;
			}
		}
	}
	return false;
}

void B_Bishop::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	int offset_eye[2] = {1, -1};
	int offset[2] = {2, -2};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			temp.x = cur.x + offset[j];
			temp.y = cur.y + offset[i];
			int eye_x = cur.x + offset_eye[j];
			int eye_y = cur.y + offset_eye[i];
			if (!is_outBoard(temp.y, temp.x) && !is_Black(board[temp.y][temp.x]) && board[eye_y][eye_x] == NoChess)
				tar_pos.push_back(temp);
		}
	}
}

bool R_Pawn::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(flagBoard[tar.y][tar.x]))
		return false;
	if (cur.y > 4)
	{
		if (tar.x == cur.x + 1 && tar.y == cur.y && !is_Red(board[tar.y][tar.x]))
			return true;
		else if (tar.x == cur.x - 1 && tar.y == cur.y && !is_Red(board[tar.y][tar.x]))
			return true;
		else if (tar.x == cur.x && tar.y == cur.y + 1 && !is_Red(board[tar.y][tar.x]))
			return true;
		else
			return false;
	}
	else
	{
		if (tar.x == cur.x && tar.y == cur.y + 1 && !is_Red(board[tar.y][tar.x]))
			return true;
		else
			return false;
	}
}

void R_Pawn::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	if (cur.y > 4)
	{
		temp.x = cur.x + 1;
		temp.y = cur.y;
		if (!is_Red(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(temp);
		temp.x = cur.x - 1;
		if (!is_Red(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(temp);
		temp.x = cur.x;
		temp.y = cur.y + 1;
		if (!is_Red(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(temp);
	}
	else
	{
		temp.x = cur.x;
		temp.y = cur.y + 1;
		if (!is_Red(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(temp);
	}
}

bool B_Pawn::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(flagBoard[tar.y][tar.x]))
		return false;
	if (cur.y < 5)
	{
		if (tar.x == cur.x + 1 && tar.y == cur.y && !is_Black(board[tar.y][tar.x]))
			return true;
		else if (tar.x == cur.x - 1 && tar.y == cur.y && !is_Black(board[tar.y][tar.x]))
			return true;
		else if (tar.x == cur.x && tar.y == cur.y - 1 && !is_Black(board[tar.y][tar.x]))
			return true;
		else
			return false;
	}
	else
	{
		if (tar.x == cur.x && tar.y == cur.y - 1 && !is_Black(board[tar.y][tar.x]))
			return true;
		else
			return false;
	}
}

void B_Pawn::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	if (cur.y < 5)
	{
		temp.x = cur.x + 1;
		temp.y = cur.y;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(temp);
		temp.x = cur.x - 1;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(temp);
		temp.x = cur.x;
		temp.y = cur.y - 1;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(temp);
	}
	else
	{
		temp.x = cur.x;
		temp.y = cur.y - 1;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(temp);
	}
}

bool R_Horse::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
	
}

void R_Horse::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
}

bool B_Horse::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
}

void B_Horse::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
}

bool R_Cannon::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
}

void R_Cannon::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
}

bool B_Cannon::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
}

void B_Cannon::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
}

bool R_Car::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
}

void R_Car::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
}

bool B_Car::moveValid(CHESSPOS &cur, CHESSPOS &tar, int board[10][9])
{
}

void B_Car::generateMovement(CHESSPOS &cur, vector<CHESSPOS> &tar_pos, int board[10][9])
{
}