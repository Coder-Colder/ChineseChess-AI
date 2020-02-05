#include "Evaluator.h"
#include <vector>
using namespace std;

//定义每种棋子的价值
#define BASEVALUE_PAWN 100
#define BASEVALUE_GUARD 250
#define BASEVALUE_BISHOP 250
#define BASEVALUE_HORSE 350
#define BASEVALUE_CANNON 350
#define BASEVALUE_CAR 500
#define BASEVALUE_KING 10000
//定义棋子灵活性
#define FLEXIBILITY_PAWN 15
#define FLEXIBILITY_GUARD 1
#define FLEXIBILITY_BISHOP 1
#define FLEXIBILITY_HORSE 12
#define FLEXIBILITY_CANNON 6
#define FLEXIBILITY_CAR 6
#define FLEXIBILITY_KING 0

//棋子位置价值
const int R_PawnOpenMidgame[10][9] = {
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   5,      0,      5,      0,      14,     0,      5,      0,      5},
	{   5,      0,      13,     0,      16,     0,      13,     0,      5},
	{   27,     35,     39,     55,     60,     55,     39,     35,     27},
	{   37,     45,     55,     60,     62,     60,     55,     45,     37},
	{   37,     48,     65,     75,     75,     75,     65,     48,     37},
	{   37,     48,     69,     85,     90,     85,     69,     48,     37},
	{   7,      8,      9,      11,     13,     11,     9,      8,      7}
};

const int B_PawnOpenMidgame[10][9] = {
	{   7,      8,      9,      11,     13,     11,     9,      8,      7},
	{   37,     48,     69,     85,     90,     85,     69,     48,     37},
	{   37,     48,     65,     75,     75,     75,     65,     48,     37},
	{   37,     45,     55,     60,     62,     60,     55,     45,     37},
	{   27,     35,     39,     55,     60,     55,     39,     35,     27},
	{   5,      0,      13,     0,      16,     0,      13,     0,      5},
	{   5,      0,      5,      0,      14,     0,      5,      0,      5},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0}
};

const int R_PawnEndgame[10][9] = {
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   40,     0,      30,     0,      40,     0,      30,     0,      40},
	{   45,     0,      40,     0,      45,     0,      40,     0,      45},
	{   68,     68,     65,     70,     70,     70,     65,     69,     68},
	{   73,     79,     80,     80,     80,     80,     80,     79,     73},
	{   63,     69,     70,     76,     76,     76,     70,     69,     63},
	{   48,     54,     60,     86,     102,    86,     60,     54,     48},
	{   8,      9,      10,     15,     15,     15,     10,     9,      8}
};

const int B_PawnEndgame[10][9] = {
	{   8,      9,      10,     15,     15,     15,     10,     9,      8},
	{   48,     54,     60,     86,     102,    86,     60,     54,     48},
	{   63,     69,     70,     76,     76,     76,     70,     69,     63},
	{   73,     79,     80,     80,     80,     80,     80,     79,     73},
	{   68,     68,     65,     70,     70,     70,     65,     69,     68},
	{   45,     0,      40,     0,      45,     0,      40,     0,      45},
	{   40,     0,      30,     0,      40,     0,      30,     0,      40},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0},
	{   0,      0,      0,      0,      0,      0,      0,      0,      0}
};

const int R_CannonOpenMidgame[10][9] = {
	{   97,     97,     98,     100,    100,    100,    98,     97,     97},
	{   97,     98,     100,    100,    100,    100,    100,    98,     97},
	{   98,     97,     102,    101,    104,    101,    102,    97,     98},
	{   97,     97,     97,     97,     97,     97,     97,     97,     97},
	{   96,     97,     100,    97,     102,    97,     100,    97,     96},
	{   97,     97,     97,     97,     102,    97,     97,     97,     97},
	{   97,     100,    100,    99,     102,    99,     100,    100,    97},
	{   98,     98,     96,     92,     93,     92,     96,     98,     98},
	{   100,    100,    96,     93,     89,     93,     96,     100,    100},
	{   102,    102,    98,     92,     90,     92,     98,     102,    102}
};

const int B_CannonOpenMidgame[10][9] = {
	{   102,    102,    98,     92,     90,     92,     98,     102,    102},
	{   100,    100,    96,     93,     89,     93,     96,     100,    100},
	{   98,     98,     96,     92,     93,     92,     96,     98,     98},
	{   97,     100,    100,    99,     102,    99,     100,    100,    97},
	{   97,     97,     97,     97,     102,    97,     97,     97,     97},
	{   96,     97,     100,    97,     102,    97,     100,    97,     96},
	{   97,     97,     97,     97,     97,     97,     97,     97,     97},
	{   98,     97,     102,    101,    104,    101,    102,    97,     98},
	{   97,     98,     100,    100,    100,    100,    100,    98,     97},
	{   97,     97,     98,     100,    100,    100,    98,     97,     97}
};

const int R_CannonEndgame[10][9] = {
	{   102,    102,    102,    106,    108,    106,    102,    102,    102},
	{   102,    102,    102,    106,    108,    106,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    102,    102,    102,    102,    102,    102},
	{   102,    102,    102,    102,    102,    102,    102,    102,    102},
	{   102,    102,    102,    102,    102,    102,    102,    102,    102}
};

const int B_CannonEndgame[10][9] = {
	{   102,    102,    102,    102,    102,    102,    102,    102,    102},
	{   102,    102,    102,    102,    102,    102,    102,    102,    102},
	{   102,    102,    102,    102,    102,    102,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    104,    106,    104,    102,    102,    102},
	{   102,    102,    102,    106,    108,    106,    102,    102,    102},
	{   102,    102,    102,    106,    108,    106,    102,    102,    102}
};

const int R_HorseOpenMidgame[10][9] = {
	{   86,     84,     90,     88,     90,     88,     90,     84,     86},
	{   83,     89,     92,     94,     78,     94,     92,     89,     83},
	{   91,     92,     94,     96,     92,     96,     94,     92,     91},
	{   90,     93,     98,     96,     98,     96,     98,     93,     90},
	{   88,     97,     100,    102,    103,    102,    100,    97,     88},
	{   88,     100,    99,     103,    104,    103,    99,     100,    88},
	{   91,     107,    100,    108,    100,    108,    100,    107,    91},
	{   90,     97,     99,     104,    99,     104,    99,     97,     90},
	{   88,     95,     104,    97,     94,     97,     104,    95,     88},
	{   88,     89,     90,     96,     90,     96,     90,     89,     88}
};

const int B_HorseOpenMidgame[10][9] = {
	{   88,     89,     90,     96,     90,     96,     90,     89,     88},
	{   88,     95,     104,    97,     94,     97,     104,    95,     88},
	{   90,     97,     99,     104,    99,     104,    99,     97,     90},
	{   91,     107,    100,    108,    100,    108,    100,    107,    91},
	{   88,     100,    99,     103,    104,    103,    99,     100,    88},
	{   88,     97,     100,    102,    103,    102,    100,    97,     88},
	{   90,     93,     98,     96,     98,     96,     98,     93,     90},
	{   91,     92,     94,     96,     92,     96,     94,     92,     91},
	{   83,     89,     92,     94,     78,     94,     92,     89,     83},
	{   86,     84,     90,     88,     90,     88,     90,     84,     86}
};

const int R_HorseEndgame[10][9] = {
	{   89,     91,     94,     91,     91,     91,     94,     91,     89},
	{   91,     93,     96,     93,     93,     93,     96,     93,     91},
	{   93,     95,     98,     98,     98,     98,     98,     95,     93},
	{   95,     97,     100,    100,    100,    100,    100,    97,     95},
	{   95,     97,     100,    100,    100,    100,    100,    97,     95},
	{   97,     99,     102,    102,    102,    102,    102,    99,     97},
	{   97,     99,     102,    102,    102,    102,    102,    99,     97},
	{   97,     99,     102,    102,    102,    102,    102,    99,     97},
	{   95,     97,     100,    100,    100,    100,    100,    97,     95},
	{   93,     95,     98,     98,     98,     98,     98,     95,     93}
};

const int B_HorseEndgame[10][9] = {
	{   93,     95,     98,     98,     98,     98,     98,     95,     93},
	{   95,     97,     100,    100,    100,    100,    100,    97,     95},
	{   97,     99,     102,    102,    102,    102,    102,    99,     97},
	{   97,     99,     102,    102,    102,    102,    102,    99,     97},
	{   97,     99,     102,    102,    102,    102,    102,    99,     97},
	{   95,     97,     100,    100,    100,    100,    100,    97,     95},
	{   95,     97,     100,    100,    100,    100,    100,    97,     95},
	{   93,     95,     98,     98,     98,     98,     98,     95,     93},
	{   91,     93,     96,     93,     93,     93,     96,     93,     91},
	{   89,     91,     94,     91,     91,     91,     94,     91,     89}
};

const int R_CarOpenMidgame[10][9] = {
	{   78,     93,     90,     90,     91,     90,     90,     93,     78},
	{   81,     93,     92,     92,     92,     92,     92,     93,     81},
	{   83,     95,     92,     92,     92,     92,     92,     95,     83},
	{   87,     96,     93,     93,     93,     93,     93,     96,     87},
	{   90,     97,     93,     94,     94,     94,     93,     97,     90},
	{   92,     99,     95,     100,    96,     100,    95,     99,     92},
	{   93,     100,    100,    102,    104,    102,    100,    100,    93},
	{   94,     102,    102,    104,    104,    104,    102,    102,    94},
	{   95,     102,    104,    104,    108,    104,    104,    102,    95},
	{   96,     104,    104,    108,    108,    108,    104,    104,    96}
};

const int B_CarOpenMidgame[10][9] = {
	{   90,     104,    104,    108,    108,    108,    104,    104,    90},
	{   95,     102,    104,    104,    108,    104,    104,    102,    95},
	{   94,     102,    102,    104,    104,    104,    102,    102,    94},
	{   93,     100,    100,    102,    104,    102,    100,    100,    93},
	{   92,     99,     95,     100,    96,     100,    95,     99,     92},
	{   90,     97,     93,     94,     94,     94,     93,     97,     90},
	{   87,     96,     93,     93,     93,     93,     93,     96,     87},
	{   83,     95,     92,     92,     92,     92,     92,     95,     83},
	{   81,     93,     92,     92,     92,     92,     92,     93,     81},
	{   78,     93,     90,     90,     91,     90,     90,     93,     78}
};

const int BaseValue[32] = {
	BASEVALUE_KING,  BASEVALUE_GUARD, BASEVALUE_GUARD,  BASEVALUE_BISHOP, BASEVALUE_BISHOP,
	BASEVALUE_PAWN,  BASEVALUE_PAWN,  BASEVALUE_PAWN,   BASEVALUE_PAWN,   BASEVALUE_PAWN,
	BASEVALUE_HORSE, BASEVALUE_HORSE, BASEVALUE_CANNON, BASEVALUE_CANNON,
	BASEVALUE_KING,  BASEVALUE_GUARD, BASEVALUE_GUARD,  BASEVALUE_BISHOP, BASEVALUE_BISHOP,
	BASEVALUE_PAWN,  BASEVALUE_PAWN,  BASEVALUE_PAWN,   BASEVALUE_PAWN,   BASEVALUE_PAWN,
	BASEVALUE_HORSE, BASEVALUE_HORSE, BASEVALUE_CANNON, BASEVALUE_CANNON
};

const int Flexibility[32] = {
	FLEXIBILITY_KING,  FLEXIBILITY_GUARD, FLEXIBILITY_GUARD,  FLEXIBILITY_BISHOP, FLEXIBILITY_BISHOP,
	FLEXIBILITY_PAWN,  FLEXIBILITY_PAWN,  FLEXIBILITY_PAWN,   FLEXIBILITY_PAWN,   FLEXIBILITY_PAWN,
	FLEXIBILITY_HORSE, FLEXIBILITY_HORSE, FLEXIBILITY_CANNON, FLEXIBILITY_CANNON,
	FLEXIBILITY_KING,  FLEXIBILITY_GUARD, FLEXIBILITY_GUARD,  FLEXIBILITY_BISHOP, FLEXIBILITY_BISHOP,
	FLEXIBILITY_PAWN,  FLEXIBILITY_PAWN,  FLEXIBILITY_PAWN,   FLEXIBILITY_PAWN,   FLEXIBILITY_PAWN,
	FLEXIBILITY_HORSE, FLEXIBILITY_HORSE, FLEXIBILITY_CANNON, FLEXIBILITY_CANNON
};

static int RedValue, BlackValue;

int getR_PawnValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BASEVALUE_PAWN;

	//位置价值
	value += R_PawnOpenMidgame[posY][posX];

	//灵活性与威胁、保护价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Red(tarChessID))//保护价值
		{
			value += BaseValue[tarChessID] / 2;
		}
		else if (is_Black(tarChessID))//威胁价值
		{
			value += (BaseValue[tarChessID] - BASEVALUE_PAWN) / 10;
			value += FLEXIBILITY_PAWN;
		}
		else//灵活性
		{
			value += FLEXIBILITY_PAWN;
		}
	}

	RedValue += value;
	return value;
}

int getB_PawnValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BASEVALUE_PAWN;

	//位置价值
	value += B_PawnOpenMidgame[posY][posX];

	//灵活性与威胁、保护价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Black(tarChessID))//保护价值
		{
			value += BaseValue[tarChessID] / 2;
		}
		else if (is_Red(tarChessID))//威胁价值
		{
			value += (BaseValue[tarChessID] - BASEVALUE_PAWN) /10;
			value += FLEXIBILITY_PAWN;
		}
		else//灵活性
		{
			value += FLEXIBILITY_PAWN;
		}
	}

	BlackValue += value;
	return value;
}

int getR_CannonValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BASEVALUE_CANNON;

	//位置价值
	value += R_CannonOpenMidgame[posY][posX];

	//灵活性与威胁、保护价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Red(tarChessID))//保护价值
		{
			if (tarChessID == R_KING)
				value += 0;
			else 
				value += BaseValue[tarChessID] / 2;
		}
		else if (is_Black(tarChessID))//威胁价值
		{
			value += (BaseValue[tarChessID] - BASEVALUE_CANNON / 5) / 10;
			value += FLEXIBILITY_CANNON;
		}
		else//灵活性
		{
			value += FLEXIBILITY_CANNON;
		}
	}

	RedValue += value;
	return value;
}

int getB_CannonValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BASEVALUE_CANNON;

	//位置价值
	value += B_CannonOpenMidgame[posY][posX];

	//灵活性与威胁、保护价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Black(tarChessID))//保护价值
		{
			if (tarChessID == B_KING)
				value += 0;
			else
				value += BaseValue[tarChessID] / 2;
		}
		else if (is_Red(tarChessID))//威胁价值
		{
			value += (BaseValue[tarChessID] - BASEVALUE_CANNON / 5) / 10;
			value += FLEXIBILITY_CANNON;
		}
		else//灵活性
		{
			value += FLEXIBILITY_CANNON;
		}
	}

	BlackValue += value;
	return value;
}

int getR_HorseValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BASEVALUE_HORSE;

	//位置价值
	value += R_HorseOpenMidgame[posY][posX];

	//灵活性与威胁、保护价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Red(tarChessID))//保护价值
		{
			if (tarChessID == R_KING)
				value += 0;
			else
				value += BaseValue[tarChessID] / 2;
		}
		else if (is_Black(tarChessID))//威胁价值
		{
			value += (BaseValue[tarChessID] - BASEVALUE_HORSE / 5) / 10;
			value += FLEXIBILITY_HORSE;
		}
		else//灵活性
		{
			value += FLEXIBILITY_HORSE;
		}
	}

	RedValue += value;
	return value;
}

int getB_HorseValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BASEVALUE_HORSE;

	//位置价值
	value += B_HorseOpenMidgame[posY][posX];

	//灵活性与威胁、保护价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Black(tarChessID))//保护价值
		{
			if (tarChessID == B_KING)
				value += 0;
			else
				value += BaseValue[tarChessID] / 2;
		}
		else if (is_Red(tarChessID))//威胁价值
		{
			value += (BaseValue[tarChessID] - BASEVALUE_HORSE / 5) / 10;
			value += FLEXIBILITY_HORSE;
		}
		else//灵活性
		{
			value += FLEXIBILITY_HORSE;
		}
	}

	BlackValue += value;
	return value;
}

int getR_CarValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BASEVALUE_CAR;

	//位置价值
	value += R_CarOpenMidgame[posY][posX];

	//灵活性与威胁、保护价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Red(tarChessID))//保护价值
		{
			if (tarChessID == R_KING)
				value += 0;
			else
				value += BaseValue[tarChessID] / 2;
		}
		else if (is_Black(tarChessID))//威胁价值
		{
			value += (BaseValue[tarChessID] - BASEVALUE_CAR / 5) / 10;
			value += FLEXIBILITY_CAR;
		}
		else//灵活性
		{
			value += FLEXIBILITY_CAR;
		}
	}

	RedValue += value;
	return value;
}

int getB_CarValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BASEVALUE_CAR;

	//位置价值
	value += B_CarOpenMidgame[posY][posX];

	//灵活性与威胁、保护价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Black(tarChessID))//保护价值
		{
			if (tarChessID == B_KING)
				value += 0;
			else
				value += BaseValue[tarChessID] / 2;
		}
		else if (is_Red(tarChessID))//威胁价值
		{
			value += (BaseValue[tarChessID] - BASEVALUE_CAR / 5) /10;
			value += FLEXIBILITY_CAR;
		}
		else//灵活性
		{
			value += FLEXIBILITY_CAR;
		}
	}

	BlackValue += value;
	return value;
}

int getR_NormalChessValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BaseValue[mChessID];
 
	//灵活性、保护、威胁价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Red(tarChessID))//保护价值
		{
			value += BaseValue[tarChessID] / 2;
		}
		else if (is_Black(tarChessID))//威胁价值
		{
			value += BaseValue[tarChessID] / 10;
			value += Flexibility[mChessID];
		}
		else//灵活性
		{
			value += Flexibility[mChessID];
		}
	}

	RedValue += value;
	return value;
}

int getB_NormalChessValue(char board[10][9], int posX, int posY)
{
	int mChessID = board[posY][posX];

	//基本价值
	int value = BaseValue[mChessID];

	//灵活性、保护、威胁价值
	vector<CHESSPOS> relate_pos;
	chess[mChessID]->genMovePos(CHESSPOS(posX, posY), relate_pos, board);

	unsigned size = relate_pos.size();
	for (unsigned i = 0; i < size; i++)
	{
		int tarChessID = board[relate_pos[i].y][relate_pos[i].x];
		if (is_Black(tarChessID))//保护价值
		{
			value += BaseValue[tarChessID] / 2;
		}
		else if (is_Red(tarChessID))//威胁价值
		{
			value += BaseValue[tarChessID] / 10;
			value += Flexibility[mChessID];
		}
		else//灵活性
		{
			value += Flexibility[mChessID];
		}
	}

	BlackValue += value;
	return value;
}

typedef int(*pfunc)(char board[10][9], int posX, int posY);

pfunc getValue[33] = {
	getR_NormalChessValue,//R_KING
	getR_NormalChessValue,//R_GUARD1
	getR_NormalChessValue,//R_GUARD2

	getR_NormalChessValue,//R_BISHOP1
	getR_NormalChessValue,//R_BISHOP2
	getR_PawnValue,//R_PAWN1
	getR_PawnValue,//R_PAWN2
	getR_PawnValue,//R_PAWN3
	getR_PawnValue,//R_PAWN4
	getR_PawnValue,//R_PAWN5
	getR_HorseValue,//R_HORSE1
	getR_HorseValue,//R_HORSE2
	getR_CannonValue,//R_CANNON1
	getR_CannonValue,//R_CANNON2
	getR_CarValue,//R_CAR1
	getR_CarValue,//R_CAR2

	getB_NormalChessValue,//B_KING
	getB_NormalChessValue,//B_GUARD1
	getB_NormalChessValue,//B_GUARD2
	getB_NormalChessValue,//B_BISHOP1
	getB_NormalChessValue,//B_BISHOP2
	getB_PawnValue,//B_PAWN1
	getB_PawnValue,//B_PAWN2
	getB_PawnValue,//B_PAWN3
	getB_PawnValue,//B_PAWN4
	getB_PawnValue,//B_PAWN5
	getB_HorseValue,//B_HORSE1
	getB_HorseValue,//B_HORSE2
	getB_CannonValue,//B_CANNON1
	getB_CannonValue,//B_CANNON2
	getB_CarValue,//B_CAR1
	getB_CarValue,//B_CAR2

	[](char board[10][9], int posX, int posY)->int {return 0; }//非棋子
};

int evaluateBoard(char board[10][9])
{
	RedValue = 0;
	BlackValue = 0;

	for(int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
			if(is_Chess(board[i][j]))
				getValue[board[i][j]](board, j, i);

	return RedValue - BlackValue;
}

int evaluateBoard(char board[10][9], Chess * chessman[32])
{
	RedValue = 0;
	BlackValue = 0;

	for (int i = 0; i < 32; i++)
		if (chessman[i]->exist)
			getValue[i](board, chessman[i]->pos.x, chessman[i]->pos.y);

	return RedValue - BlackValue;
}

int evaluateMove(MOVEMENT & mvmt, char board[10][9])
{
	int mChessID = board[mvmt.src.y][mvmt.src.x];
	if(is_Red(mChessID))
	{
		//计算移动前
		int value = getValue[mChessID](board, mvmt.src.x, mvmt.src.y);

		//计算移动后
	}
	else
	{

	}
}