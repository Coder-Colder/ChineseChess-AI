#include "Chess.h"
#include <vector>
bool twoKingMeet(CHESSPOS &pos, CHESSPOS &tar, int board[10][9])
{
	CHESSPOS R_King_Pos;
	getRKing(R_King_Pos, board);
	CHESSPOS B_King_Pos;
	getBKing(B_King_Pos, board);
	//先检查两王是否在一条线上，在检查当前棋子是否在两王之间
	if (R_King_Pos.x == B_King_Pos.x && R_King_Pos.x == pos.x && pos.x != tar.x && pos.y > R_King_Pos.y && pos.y < B_King_Pos.y)
	{
		//确定当前棋子是两王之间唯一的棋子
		for (int i = pos.y; i < B_King_Pos.y; i++)
		{
			if (board[i][pos.x] != 0)
				return false;
		}
		for (int i = pos.y; i > R_King_Pos.y; i--)
		{
			if (board[i][pos.x] != 0)
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
			if (board[i][j] == R_KING)
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

bool R_King::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(tar.y, tar.x))
		return false;
	//上下左右四个方向判断
	if ((tar.x != pos.x + 1 || tar.x != pos.x - 1) && tar.y == pos.y)
		return false;
	if ((tar.y != pos.y + 1 || tar.y != pos.y - 1) && tar.x == pos.x)
		return false;
	if (is_Red(board[tar.y][tar.x]))
		return false;
	//检查二王相见
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

void R_King::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	int offset[2] = {1, -1}; //辅助数组，便于循环
	CHESSPOS temp;
	//判断上下两个位置
	for (int i = 0; i < 2; i++)
	{
		temp.x = pos.x;
		temp.y = pos.y + offset[i];
		if (!is_Red(board[temp.y][temp.x]) && !is_outRedPalace(temp.y, temp.x))
		{
			tar_pos.push_back(MOVEMENT(pos,temp));
		}
	}
	//判断左右两个位置
	for (int i = 0; i < 2; i++)
	{
		temp.x = pos.x + offset[i];
		temp.y = pos.y;
		if (!is_Red(board[temp.y][temp.x]) && !is_outRedPalace(temp.y, temp.x))
		{
			tar_pos.push_back(MOVEMENT(pos,temp));
		}
	}
}

bool B_King::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(tar.y, tar.x))
		return false;
	//上下左右四个方向判断
	if ((tar.x != pos.x + 1 || tar.x != pos.x - 1) && tar.y == pos.y)
		return false;
	if ((tar.y != pos.y + 1 || tar.y != pos.y - 1) && tar.x == pos.x)
		return false;
	if (is_Black(board[tar.y][tar.x]))
		return false;
	//检查二王相见
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

void B_King::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	int offset[2] = {1, -1}; //辅助数组，便于循环
	CHESSPOS temp;
	//判断上下两个位置
	for (int i = 0; i < 2; i++)
	{
		temp.x = pos.x;
		temp.y = pos.y + offset[i];
		if (!is_Black(board[temp.y][temp.x]) && !is_outBlackPalace(temp.y, temp.x))
		{
			tar_pos.push_back(MOVEMENT(pos,temp));
		}
	}
	//判断左右两个位置
	for (int i = 0; i < 2; i++)
	{
		temp.x = pos.x + offset[i];
		temp.y = pos.y;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBlackPalace(temp.y, temp.x))
		{
			tar_pos.push_back(MOVEMENT(pos,temp));
		}
	}
}

bool R_Guard::moveValid(CHESSPOS &tar, int board[10][9])
{
	//士在九宫中心，可能走4个位置
	if (pos.y == 1 && pos.x == 4)
	{
		//用循环对四个位置进行判断
		int offset_x[2] = {3, 5};
		int offset_y[2] = {0, 2};
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (tar.x == offset_x[i] && tar.y == offset_y[j] && !is_Red(board[tar.y][tar.x]) && !twoKingMeet(pos, tar, board))
					return true;
			}
		}
	}
	//士在九宫4角，只可能走到中心
	else
	{
		if (tar.x == 4 && tar.y == 1 && !is_Red(board[1][4]) && !twoKingMeet(pos, tar, board))
			return true;
	}
	return false;
}

void R_Guard::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	//同理对4角是否能走进行判断
	if (pos.y == 1 && pos.x == 4)
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
					tar_pos.push_back(MOVEMENT(pos,temp));
				}
			}
		}
	}
	else
	{
		temp.x = 4;
		temp.y = 1;
		if (!is_Red(board[1][4]))
			tar_pos.push_back(MOVEMENT(pos,temp));
	}
}

bool B_Guard::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (pos.y == 8 && pos.x == 4)
	{
		int offset_x[2] = {3, 5};
		int offset_y[2] = {7, 9};
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (tar.x == offset_x[i] && tar.y == offset_y[j] && !is_Black(board[tar.y][tar.x]) && !twoKingMeet(pos, tar, board))
					return true;
			}
		}
	}
	else
	{
		if (tar.x == 4 && tar.y == 8 && !is_Black(board[8][4]) && !twoKingMeet(pos, tar, board))
			return true;
	}
	return false;
}

void B_Guard::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	if (pos.y == 1 && pos.x == 4)
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
					tar_pos.push_back(MOVEMENT(pos,temp));
				}
			}
		}
	}
	else
	{
		temp.x = 4;
		temp.y = 8;
		if (!is_Red(board[8][4]))
			tar_pos.push_back(MOVEMENT(pos,temp));
	}
}

bool R_Bishop::moveValid(CHESSPOS &tar, int board[10][9])
{
	//两个辅助数组，用于在循环找到象眼和可以走的位置
	int offset_eye[2] = {1, -1};
	int offset[2] = {2, -2};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int eye_x = pos.x + offset_eye[j];
			int eye_y = pos.y + offset_eye[i];
			if (tar.x == pos.x + offset[j] && tar.y == pos.y + offset[i] && !is_Red(board[tar.y][tar.x]) && board[eye_y][eye_x] == NoChess && !twoKingMeet(pos, tar, board))
			{
				return true;
			}
		}
	}
	return false;
}

void R_Bishop::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	int offset_eye[2] = {1, -1};
	int offset[2] = {2, -2};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			temp.x = pos.x + offset[j];
			temp.y = pos.y + offset[i];
			int eye_x = pos.x + offset_eye[j];
			int eye_y = pos.y + offset_eye[i];
			if (!is_outBoard(temp.y, temp.x) && !is_Red(board[temp.y][temp.x]) && board[eye_y][eye_x] == NoChess)
				tar_pos.push_back(MOVEMENT(pos,temp));
		}
	}
}

bool B_Bishop::moveValid(CHESSPOS &tar, int board[10][9])
{
	int offset_eye[2] = {1, -1};
	int offset[2] = {2, -2};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int eye_x = pos.x + offset_eye[j];
			int eye_y = pos.y + offset_eye[i];
			if (tar.x == pos.x + offset[j] && tar.y == pos.y + offset[i] && !is_Black(board[tar.y][tar.x]) && board[eye_y][eye_x] == NoChess && !twoKingMeet(pos, tar, board))
			{
				return true;
			}
		}
	}
	return false;
}

void B_Bishop::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	int offset_eye[2] = {1, -1};
	int offset[2] = {2, -2};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			temp.x = pos.x + offset[j];
			temp.y = pos.y + offset[i];
			int eye_x = pos.x + offset_eye[j];
			int eye_y = pos.y + offset_eye[i];
			if (!is_outBoard(temp.y, temp.x) && !is_Black(board[temp.y][temp.x]) && board[eye_y][eye_x] == NoChess)
				tar_pos.push_back(MOVEMENT(pos,temp));
		}
	}
}

bool R_Pawn::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (twoKingMeet(pos, tar, board))
		return false;
	//兵过河的情况，有3种走法，分别判断
	if (pos.y > 4)
	{
		if (tar.x == pos.x + 1 && tar.y == pos.y && !is_Red(board[tar.y][tar.x]))
			return true;
		else if (tar.x == pos.x - 1 && tar.y == pos.y && !is_Red(board[tar.y][tar.x]))
			return true;
		else if (tar.x == pos.x && tar.y == pos.y + 1 && !is_Red(board[tar.y][tar.x]))
			return true;
		else
			return false;
	}
	//兵没有过河，只有一种走法
	else
	{
		if (tar.x == pos.x && tar.y == pos.y + 1 && !is_Red(board[tar.y][tar.x]))
			return true;
		else
			return false;
	}
}

void R_Pawn::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	//同理，兵过河的情况，有3种走法，分别判断
	if (pos.y > 4)
	{
		temp.x = pos.x + 1;
		temp.y = pos.y;
		if (!is_Red(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(MOVEMENT(pos,temp));
		temp.x = pos.x - 1;
		if (!is_Red(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(MOVEMENT(pos,temp));
		temp.x = pos.x;
		temp.y = pos.y + 1;
		if (!is_Red(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(MOVEMENT(pos,temp));
	}
	else
	{
		temp.x = pos.x;
		temp.y = pos.y + 1;
		if (!is_Red(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(MOVEMENT(pos,temp));
	}
}

bool B_Pawn::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (twoKingMeet(pos, tar, board))
		return false;
	if (pos.y < 5)
	{
		if (tar.x == pos.x + 1 && tar.y == pos.y && !is_Black(board[tar.y][tar.x]))
			return true;
		else if (tar.x == pos.x - 1 && tar.y == pos.y && !is_Black(board[tar.y][tar.x]))
			return true;
		else if (tar.x == pos.x && tar.y == pos.y - 1 && !is_Black(board[tar.y][tar.x]))
			return true;
		else
			return false;
	}
	else
	{
		if (tar.x == pos.x && tar.y == pos.y - 1 && !is_Black(board[tar.y][tar.x]))
			return true;
		else
			return false;
	}
}

void B_Pawn::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	if (pos.y < 5)
	{
		temp.x = pos.x + 1;
		temp.y = pos.y;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(MOVEMENT(pos,temp));
		temp.x = pos.x - 1;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(MOVEMENT(pos,temp));
		temp.x = pos.x;
		temp.y = pos.y - 1;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(MOVEMENT(pos,temp));
	}
	else
	{
		temp.x = pos.x;
		temp.y = pos.y - 1;
		if (!is_Black(board[temp.y][temp.x]) && !is_outBoard(temp.y, temp.x))
			tar_pos.push_back(MOVEMENT(pos,temp));
	}
}

bool R_Horse::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (twoKingMeet(pos, tar, board))
		return false;
	//辅助数组，便于在循环中找到马眼的位置
	int offset_eye_x[4] = {0, 0, 1, -1};
	int offset_eye_y[4] = {1, -1, 0, 0};
	//辅助数组，便于在循环中找到马可以跳的位置
	int offset_x[8] = {1, -1, 1, -1, 2, 2, -2, -2};
	int offset_y[8] = {2, 2, -2, -2, 1, -1, 1, -1};
	for (int i = 0; i < 8; i++)
	{
		if (tar.x == pos.x + offset_x[i] && tar.y == pos.y + offset_y[i] && !is_outBoard(tar.y, tar.x) && !is_Red(board[tar.y][tar.x]))
		{
			int eye_x = pos.x + offset_eye_x[i / 2];
			int eye_y = pos.y + offset_eye_y[i / 2];
			if (!is_outBoard(eye_y, eye_x) && board[eye_y][eye_x] == NoChess)
				return true;
		}
	}
	return false;
}

void R_Horse::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	//辅助数组，便于在循环中找到马眼的位置
	int offset_eye_x[4] = {0, 0, 1, -1};
	int offset_eye_y[4] = {1, -1, 0, 0};
	//辅助数组，便于在循环中找到马可以跳的位置
	int offset_x[8] = {1, -1, 1, -1, 2, 2, -2, -2};
	int offset_y[8] = {2, 2, -2, -2, 1, -1, 1, -1};
	for (int i = 0; i < 4; i++)
	{
		//判断马眼是否被堵住
		int eye_x = pos.x + offset_eye_x[i];
		int eye_y = pos.y + offset_eye_y[i];
		if (!is_outBoard(eye_y, eye_x) && board[eye_y][eye_x] == NoChess)
		{
			//若没有被堵住，则判断对应的两个位置是否可以走
			for (int k = 0; k < 2; k++)
			{
				temp.x = pos.x + offset_x[i * 2 + k];
				temp.y = pos.y + offset_y[i * 2 + k];
				if (!is_outBoard(temp.y, temp.x) && !is_Red(board[temp.y][temp.x]))
					tar_pos.push_back(MOVEMENT(pos,temp));
			}
		}
	}
}

bool B_Horse::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (twoKingMeet(pos, tar, board))
		return false;
	//辅助数组，便于在循环中找到马眼的位置
	int offset_eye_x[4] = {0, 0, 1, -1};
	int offset_eye_y[4] = {1, -1, 0, 0};
	//辅助数组，便于在循环中找到马可以跳的位置
	int offset_x[8] = {1, -1, 1, -1, 2, 2, -2, -2};
	int offset_y[8] = {2, 2, -2, -2, 1, -1, 1, -1};
	for (int i = 0; i < 8; i++)
	{
		if (tar.x == pos.x + offset_x[i] && tar.y == pos.y + offset_y[i] && !is_outBoard(tar.y, tar.x) && !is_Black(board[tar.y][tar.x]))
		{
			int eye_x = pos.x + offset_eye_x[i / 2];
			int eye_y = pos.y + offset_eye_y[i / 2];
			if (!is_outBoard(eye_y, eye_x) && board[eye_y][eye_x] == NoChess)
				return true;
		}
	}
	return false;
}

void B_Horse::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	CHESSPOS temp;
	//辅助数组，便于在循环中找到马眼的位置
	int offset_eye_x[4] = {0, 0, 1, -1};
	int offset_eye_y[4] = {1, -1, 0, 0};
	//辅助数组，便于在循环中找到马可以跳的位置
	int offset_x[8] = {1, -1, 1, -1, 2, 2, -2, -2};
	int offset_y[8] = {2, 2, -2, -2, 1, -1, 1, -1};
	for (int i = 0; i < 4 ; i++)
	{
		//判断马眼是否被堵住
		int eye_x = pos.x + offset_eye_x[i];
		int eye_y = pos.y + offset_eye_y[i];
		if (!is_outBoard(eye_y, eye_x) && board[eye_y][eye_x] == NoChess)
		{
			//若没有被堵住，则判断对应的两个位置是否可以走
			for (int k = 0; k < 2; k++)
			{
				temp.x = pos.x + offset_x[i * 2 + k];
				temp.y = pos.y + offset_y[i * 2 + k];
				if (!is_outBoard(temp.y, temp.x) && !is_Black(board[temp.y][temp.x]))
					tar_pos.push_back(MOVEMENT(pos,temp));
			}
		}
	}
}

bool R_Cannon::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(tar.y, tar.x) || twoKingMeet(pos, tar, board))
		return false;
	//先判断是否在一条直线上
	if (tar.x != pos.x && tar.y != pos.y)
		return false;
	//根据目的地的棋子类型分类
	//目的地无棋子，进行移动
	if (board[tar.y][tar.x] == NoChess)
	{
		//确定路线上没有棋子
		if (tar.x == pos.x)
		{
			if (tar.y > pos.y)
			{
				for (int i = pos.y + 1; i < tar.y; i++)
					if (board[i][pos.x] != NoChess)
						return false;
				return true;
			}
			else
			{
				for (int i = pos.y - 1; i > tar.y; i--)
					if (board[i][pos.x] != NoChess)
						return false;
				return true;
			}
		}
		else
		{
			if (tar.x > pos.x)
			{
				for (int i = pos.x + 1; i < tar.x; i++)
					if (board[pos.y][i] != NoChess)
						return false;
				return true;
			}
			else
			{
				for (int i = pos.x - 1; i > tar.x; i--)
					if (board[pos.y][i] != NoChess)
						return false;
				return true;
			}
		}
	}
	//目的地为黑棋，吃子
	else if (is_Black(board[tar.y][tar.x]))
	{
		//确定路线上只有一颗棋子
		bool flag = false; //标志是否存在跳板
		if (tar.x == pos.x)
		{
			if (tar.y > pos.y)
			{
				for (int i = pos.y + 1; i < tar.y; i++)
				{
					//发现跳板
					if (board[i][pos.x] != NoChess && flag == false)
						flag = true;
					//多于一颗棋子
					else if (board[i][pos.x] != NoChess)
						return false;
				}
				//判断是否存在跳板
				if (flag)
					return true;
				else
					return false;
			}
			else
			{
				for (int i = pos.y - 1; i > tar.y; i--)
				{
					//发现跳板
					if (board[i][pos.x] != NoChess && flag == false)
						flag = true;
					//多于一颗棋子
					else if (board[i][pos.x] != NoChess)
						return false;
				}
				//判断是否存在跳板
				if (flag)
					return true;
				else
					return false;
			}
		}
		else
		{
			if (tar.x > pos.x)
			{
				for (int i = pos.x + 1; i < tar.x; i++)
				{
					//发现跳板
					if (board[pos.y][i] != NoChess && flag == false)
						flag = true;
					//多于一颗棋子
					else if (board[pos.y][i] != NoChess)
						return false;
				}
				//判断是否存在跳板
				if (flag)
					return true;
				else
					return false;
			}
			else
			{
				for (int i = pos.x - 1; i > tar.x; i--)
				{
					//发现跳板
					if (board[pos.y][i] != NoChess && flag == false)
						flag = true;
					//多于一颗棋子
					else if (board[pos.y][i] != NoChess)
						return false;
				}
				//判断是否存在跳板
				if (flag)
					return true;
				else
					return false;
			}
		}
	}
	//为红棋，不合法
	else
		return false;
}

void R_Cannon::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	//分方向进行寻找
	//向右寻找
	for (int i = pos.x + 1; i < 9; i++)
	{
		//首先加入可以移动的所有位置
		if (board[pos.y][i] == NoChess)
			tar_pos.push_back(CHESSPOS(i, pos.y));
		else
		{
			//碰到跳板后，寻找跳板之后的第一颗棋子
			for (int j = i + 1; j < 9; j++)
			{
				//为黑，可以吃掉
				if (is_Black(board[pos.y][j]))
					tar_pos.push_back(CHESSPOS(j, pos.y));
				//为红，不可以退出循环
				else if (is_Red(board[pos.y][j]))
					break;
			}
			break;
		}
	}
	//向左寻找
	for (int i = pos.x - 1; i > 0; i--)
	{
		if (board[pos.y][i] == NoChess)
			tar_pos.push_back(CHESSPOS(i, pos.y));
		else
		{
			//碰到跳板后，寻找跳板之后的第一颗棋子
			for (int j = i - 1; j > 0; j--)
			{
				//为黑，可以吃掉
				if (is_Black(board[pos.y][j]))
					tar_pos.push_back(CHESSPOS(j, pos.y));
				//为红，不可以退出循环
				else if (is_Red(board[pos.y][j]))
					break;
			}
			break;
		}
	}
	//向下寻找
	for (int i = pos.y + 1; i < 10; i++)
	{
		//首先加入可以移动的所有位置
		if (board[i][pos.x] == NoChess)
			tar_pos.push_back(CHESSPOS(pos.x, i));
		else
		{
			//碰到跳板后，寻找跳板之后的第一颗棋子
			for (int j = i + 1; j < 10; j++)
			{
				//为黑，可以吃掉
				if (is_Black(board[j][pos.x]))
					tar_pos.push_back(CHESSPOS(pos.x, j));
				//为红，不可以退出循环
				else if (is_Red(board[j][pos.x]))
					break;
			}
			break;
		}
	}
	//向上寻找
	for (int i = pos.y - 1; i > 0; i--)
	{
		//首先加入可以移动的所有位置
		if (board[i][pos.x] == NoChess)
			tar_pos.push_back(CHESSPOS(pos.x, i));
		else
		{
			//碰到跳板后，寻找跳板之后的第一颗棋子
			for (int j = i - 1; j > 0; j--)
			{
				//为黑，可以吃掉
				if (is_Black(board[j][pos.x]))
					tar_pos.push_back(CHESSPOS(pos.x, j));
				//为红，不可以退出循环
				else if (is_Red(board[j][pos.x]))
					break;
			}
			break;
		}
	}
}

bool B_Cannon::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(tar.y, tar.x) || twoKingMeet(pos, tar, board))
		return false;
	//先判断是否在一条直线上
	if (tar.x != pos.x && tar.y != pos.y)
		return false;
	//根据目的地的棋子类型分类
	//目的地无棋子，进行移动
	if (board[tar.y][tar.x] == NoChess)
	{
		//确定路线上没有棋子
		if (tar.x == pos.x)
		{
			if (tar.y > pos.y)
			{
				for (int i = pos.y + 1; i < tar.y; i++)
					if (board[i][pos.x] != NoChess)
						return false;
				return true;
			}
			else
			{
				for (int i = pos.y - 1; i > tar.y; i--)
					if (board[i][pos.x] != NoChess)
						return false;
				return true;
			}
		}
		else
		{
			if (tar.x > pos.x)
			{
				for (int i = pos.x + 1; i < tar.x; i++)
					if (board[pos.y][i] != NoChess)
						return false;
				return true;
			}
			else
			{
				for (int i = pos.x - 1; i > tar.x; i--)
					if (board[pos.y][i] != NoChess)
						return false;
				return true;
			}
		}
	}
	//目的地为红棋，吃子
	else if (is_Red(board[tar.y][tar.x]))
	{
		//确定路线上只有一颗棋子
		bool flag = false; //标志是否存在跳板
		if (tar.x == pos.x)
		{
			if (tar.y > pos.y)
			{
				for (int i = pos.y + 1; i < tar.y; i++)
				{
					//发现跳板
					if (board[i][pos.x] != NoChess && flag == false)
						flag = true;
					//多于一颗棋子
					else if (board[i][pos.x] != NoChess)
						return false;
				}
				//判断是否存在跳板
				if (flag)
					return true;
				else
					return false;
			}
			else
			{
				for (int i = pos.y - 1; i > tar.y; i--)
				{
					//发现跳板
					if (board[i][pos.x] != NoChess && flag == false)
						flag = true;
					//多于一颗棋子
					else if (board[i][pos.x] != NoChess)
						return false;
				}
				//判断是否存在跳板
				if (flag)
					return true;
				else
					return false;
			}
		}
		else
		{
			if (tar.x > pos.x)
			{
				for (int i = pos.x + 1; i < tar.x; i++)
				{
					//发现跳板
					if (board[pos.y][i] != NoChess && flag == false)
						flag = true;
					//多于一颗棋子
					else if (board[pos.y][i] != NoChess)
						return false;
				}
				//判断是否存在跳板
				if (flag)
					return true;
				else
					return false;
			}
			else
			{
				for (int i = pos.x - 1; i > tar.x; i--)
				{
					//发现跳板
					if (board[pos.y][i] != NoChess && flag == false)
						flag = true;
					//多于一颗棋子
					else if (board[pos.y][i] != NoChess)
						return false;
				}
				//判断是否存在跳板
				if (flag)
					return true;
				else
					return false;
			}
		}
	}
	//为黑棋，不合法
	else
		return false;
}

void B_Cannon::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	//分方向进行寻找
	//向右寻找
	for (int i = pos.x + 1; i < 9; i++)
	{
		//首先加入可以移动的所有位置
		if (board[pos.y][i] == NoChess)
			tar_pos.push_back(CHESSPOS(i, pos.y));
		else
		{
			//碰到跳板后，寻找跳板之后的第一颗棋子
			for (int j = i + 1; j < 9; j++)
			{
				//为红，可以吃掉
				if (is_Red(board[pos.y][j]))
					tar_pos.push_back(CHESSPOS(j, pos.y));
				//为黑，不可以退出循环
				else if (is_Black(board[pos.y][j]))
					break;
			}
			break;
		}
	}
	//向左寻找
	for (int i = pos.x -1; i > 0; i--)
	{
		if (board[pos.y][i] == NoChess)
			tar_pos.push_back(CHESSPOS(i, pos.y));
		else
		{
			//碰到跳板后，寻找跳板之后的第一颗棋子
			for (int j = i - 1; j > 0; j--)
			{
				//为红，可以吃掉
				if (is_Red(board[pos.y][j]))
					tar_pos.push_back(CHESSPOS(j, pos.y));
				//为黑，不可以退出循环
				else if (is_Black(board[pos.y][j]))
					break;
			}
			break;
		}
	}
	//向下寻找
	for (int i = pos.y + 1; i < 10; i++)
	{
		//首先加入可以移动的所有位置
		if (board[i][pos.x] == NoChess)
			tar_pos.push_back(CHESSPOS(pos.x, i));
		else
		{
			//碰到跳板后，寻找跳板之后的第一颗棋子
			for (int j = i + 1; j < 10; j++)
			{
				//为红，可以吃掉
				if (is_Red(board[j][pos.x]))
					tar_pos.push_back(CHESSPOS(pos.x, j));
				//为黑，不可以退出循环
				else if (is_Black(board[j][pos.x]))
					break;
			}
			break;
		}
	}
	//向上寻找
	for (int i = pos.y - 1; i > 0; i--)
	{
		//首先加入可以移动的所有位置
		if (board[i][pos.x] == NoChess)
			tar_pos.push_back(CHESSPOS(pos.x, i));
		else
		{
			//碰到跳板后，寻找跳板之后的第一颗棋子
			for (int j = i - 1; j > 0; j--)
			{
				//为红，可以吃掉
				if (is_Red(board[j][pos.x]))
					tar_pos.push_back(CHESSPOS(pos.x, j));
				//为黑，不可以退出循环
				else if (is_Black(board[j][pos.x]))
					break;
			}
			break;
		}
	}
}

bool R_Car::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(tar.y, tar.x) || twoKingMeet(pos, tar, board))
		return false;
	//先判断是否在一条直线上
	if (tar.x != pos.x && tar.y != pos.y)
		return false;
	//根据目的地的棋子类型分类
	//目的地无棋子或者为黑棋，进行移动或吃子
	if (!is_Red(board[tar.y][tar.x]))
	{
		//确定路线上没有棋子
		if (tar.x == pos.x)
		{
			if (tar.y > pos.y)
			{
				for (int i = pos.y + 1; i < tar.y; i++)
					if (board[i][pos.x] != NoChess)
						return false;
				return true;
			}
			else
			{
				for (int i = pos.y - 1; i > tar.y; i--)
					if (board[i][pos.x] != NoChess)
						return false;
				return true;
			}
		}
		else
		{
			if (tar.x > pos.x)
			{
				for (int i = pos.x + 1; i < tar.x; i++)
					if (board[pos.y][i] != NoChess)
						return false;
				return true;
			}
			else
			{
				for (int i = pos.x - 1; i > tar.x; i--)
					if (board[pos.y][i] != NoChess)
						return false;
				return true;
			}
		}
	}
	//为红棋，不合法
	else
		return false;
}

void R_Car::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	//分方向进行寻找
	//向右寻找
	for (int i = pos.x + 1; i < 9; i++)
	{
		//首先加入可以移动的所有位置
		if (board[pos.y][i] == NoChess)
			tar_pos.push_back(CHESSPOS(i, pos.y));
		else
		{
			//碰到第一颗棋子后，查看对应的属性
			//为黑，可以吃掉
			if (is_Black(board[pos.y][i]))
				tar_pos.push_back(CHESSPOS(i, pos.y));
			break;
		}
	}
	//向左寻找
	for (int i = pos.x - 1; i > 0; i--)
	{
		if (board[pos.y][i] == NoChess)
			tar_pos.push_back(CHESSPOS(i, pos.y));
		else
		{
			//碰到第一颗棋子后，查看对应的属性
			//为黑，可以吃掉
			if (is_Black(board[pos.y][i]))
				tar_pos.push_back(CHESSPOS(i, pos.y));
			break;
		}
	}
	//向下寻找
	for (int i = pos.y + 1; i < 10; i++)
	{
		//首先加入可以移动的所有位置
		if (board[i][pos.x] == NoChess)
			tar_pos.push_back(CHESSPOS(pos.x, i));
		else
		{
			//碰到第一颗棋子后，查看对应的属性
			//为黑，可以吃掉
			if (is_Black(board[i][pos.x]))
				tar_pos.push_back(CHESSPOS(pos.x, i));
			break;
		}
	}
	//向上寻找
	for (int i = pos.y - 1; i > 0; i--)
	{
		//首先加入可以移动的所有位置
		if (board[i][pos.x] == NoChess)
			tar_pos.push_back(CHESSPOS(pos.x, i));
		else
		{
			//碰到第一颗棋子后，查看对应的属性
			//为黑，可以吃掉
			if (is_Black(board[i][pos.x]))
				tar_pos.push_back(CHESSPOS(pos.x, i));
			break;
		}
	}
}

bool B_Car::moveValid(CHESSPOS &tar, int board[10][9])
{
	if (is_outBoard(tar.y, tar.x) || twoKingMeet(pos, tar, board))
		return false;
	//先判断是否在一条直线上
	if (tar.x != pos.x && tar.y != pos.y)
		return false;
	//根据目的地的棋子类型分类
	//目的地无棋子或者为红棋，进行移动或吃子
	if (!is_Black(board[tar.y][tar.x]))
	{
		//确定路线上没有棋子
		if (tar.x == pos.x)
		{
			if (tar.y > pos.y)
			{
				for (int i = pos.y + 1; i < tar.y; i++)
					if (board[i][pos.x] != NoChess)
						return false;
				return true;
			}
			else
			{
				for (int i = pos.y - 1; i > tar.y; i--)
					if (board[i][pos.x] != NoChess)
						return false;
				return true;
			}
		}
		else
		{
			if (tar.x > pos.x)
			{
				for (int i = pos.x + 1; i < tar.x; i++)
					if (board[pos.y][i] != NoChess)
						return false;
				return true;
			}
			else
			{
				for (int i = pos.x - 1; i > tar.x; i--)
					if (board[pos.y][i] != NoChess)
						return false;
				return true;
			}
		}
	}
	//为黑棋，不合法
	else
		return false;
}

void B_Car::generateMovement(vector<MOVEMENT> &tar_pos, int board[10][9])
{
	//分方向进行寻找
	//向右寻找
	for (int i = pos.x + 1; i < 9; i++)
	{
		//首先加入可以移动的所有位置
		if (board[pos.y][i] == NoChess)
			tar_pos.push_back(CHESSPOS(i, pos.y));
		else
		{
			//碰到第一颗棋子后，查看对应的属性
			//为红，可以吃掉
			if (is_Red(board[pos.y][i]))
				tar_pos.push_back(CHESSPOS(i, pos.y));
			break;
		}
	}
	//向左寻找
	for (int i = pos.x - 1; i > 0; i--)
	{
		if (board[pos.y][i] == NoChess)
			tar_pos.push_back(CHESSPOS(i, pos.y));
		else
		{
			//碰到第一颗棋子后，查看对应的属性
			//为红，可以吃掉
			if (is_Red(board[pos.y][i]))
				tar_pos.push_back(CHESSPOS(i, pos.y));
			break;
		}
	}
	//向下寻找
	for (int i = pos.y + 1; i < 10; i++)
	{
		//首先加入可以移动的所有位置
		if (board[i][pos.x] == NoChess)
			tar_pos.push_back(CHESSPOS(pos.x, i));
		else
		{
			//碰到第一颗棋子后，查看对应的属性
			//为红，可以吃掉
			if (is_Red(board[i][pos.x]))
				tar_pos.push_back(CHESSPOS(pos.x, i));
			break;
		}
	}
	//向上寻找
	for (int i = pos.y - 1; i > 0; i--)
	{
		//首先加入可以移动的所有位置
		if (board[i][pos.x] == NoChess)
			tar_pos.push_back(CHESSPOS(pos.x, i));
		else
		{
			//碰到第一颗棋子后，查看对应的属性
			//为红，可以吃掉
			if (is_Red(board[i][pos.x]))
				tar_pos.push_back(CHESSPOS(pos.x, i));
			break;
		}
	}
}

/*

ToDo:一个需要注意的地方，有些棋子tar可以和pos相同，有些不可以

*/
