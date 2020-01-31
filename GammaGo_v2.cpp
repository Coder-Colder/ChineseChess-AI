#include "GammaGo_v2.h"
#include <cmath>
#include <ctime>
#include <random>
#include <cassert>
#include <iostream>
using namespace std;

static unsigned node_cnt = 0;//记录搜素过的节点数
static default_random_engine e;
static uniform_int_distribution<unsigned> red_no(RedBegin, RedEnd);
static uniform_int_distribution<unsigned> black_no(BlackBegin, BlackEnd);

void GammaGo_v2::display()
{
	cout << endl << endl;
	cout << "  ";
	for (int i = 0; i < 9; i++)
		cout << i << "      ";
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 9; j++)
		{
			switch (m_board[i][j])
			{
			case R_KING:cout << "帥";
				break;
			case B_KING:cout << "将";
				break;
			case R_GUARD1:
			case R_GUARD2:cout << "仕";
				break;
			case B_GUARD1:
			case B_GUARD2:cout << "士";
				break;
			case R_HORSE1:
			case R_HORSE2:cout << "馬";
				break;
			case B_HORSE1:
			case B_HORSE2:cout << "马";
				break;
			case R_BISHOP1:
			case R_BISHOP2:cout << "相";
				break;
			case B_BISHOP1:
			case B_BISHOP2:cout << "象";
				break;
			case R_CANNON1:
			case R_CANNON2:cout << "砲";
				break;
			case B_CANNON1:
			case B_CANNON2:cout << "炮";
				break;
			case R_CAR1:
			case R_CAR2:cout << "車";
				break;
			case B_CAR1:
			case B_CAR2:cout << "车";
				break;
			case R_PAWN1:
			case R_PAWN2:
			case R_PAWN3:
			case R_PAWN4:
			case R_PAWN5:cout << "兵";
				break;
			case B_PAWN1:
			case B_PAWN2:
			case B_PAWN3:
			case B_PAWN4:
			case B_PAWN5:cout << "卒";
				break;
			case NoChess:cout << "+-";
				break;
			}
			if (j != 8)cout << "-----";
		}
		cout << endl;
		switch (i)
		{
		case 9:
			break;
		case 0:
		case 7:
			cout << "  |      |      |      |  \\   |   /  |      |      |      |" << endl;
			cout << "  |      |      |      |    \\ | /    |      |      |      |" << endl;
			break;
		case 1:
		case 8:
			cout << "  |      |      |      |    / | \\    |      |      |      |" << endl;
			cout << "  |      |      |      |  /   |   \\  |      |      |      |" << endl;
			break;
		case 4:
			cout << "  |         楚                          汉                |" << endl;
			cout << "  |                河                          界         |" << endl;
			break;
		case 2:
			cout << "  |      |      |      |      |      |      |      |      |        红" << endl;
			cout << "  |      |      |      |      |      |      |      |      |" << endl;
			break;
		case 6:
			cout << "  |      |      |      |      |      |      |      |      |" << endl;
			cout << "  |      |      |      |      |      |      |      |      |        黑" << endl;
			break;
		default:
			cout << "  |      |      |      |      |      |      |      |      |" << endl;
			cout << "  |      |      |      |      |      |      |      |      |" << endl;
			break;
		}
	}
}

bool UCTNode::operator>(const UCTNode & node)
{
	double base0 = 2 * log(node_cnt);
	double m_reliable = (double)win_cnt / (double)hit_cnt + CONFINDENCE * sqrt((double)(base0 / (double)hit_cnt));
	double n_reliable = (double)node.win_cnt / (double)node.hit_cnt + CONFINDENCE * sqrt((double)(base0 / (double)node.hit_cnt));
	double off = m_reliable - n_reliable;
	//先判等
	if (fabs(off) < 0.000001)
		return false;
	else
		return off > 0;
}

void UCTNode::adjust()//最大堆的调整算法
{
	if (tail == childs.size() - 1)//所有子节点全部搜索完，采用siftDown策略
	{
		UCTNode * temp = childs[0];
		int i = 0, j = 2 * i + 1;
		while (j <= tail)
		{
			if (j + 1 <= tail && *childs[j + 1] > *childs[j])j++;
			if (*childs[j] > *temp)
			{
				childs[i] = childs[j];
				i = j;
				j = 2 * i + 1;
			}
			else
				break;
		}
		childs[i] = temp;
	}
	else//child[tial]是新加入搜索树的结点，未加入堆中，采用siftUp策略
	{
		UCTNode * temp = childs[tail];
		int i = tail, j = (i - 1)/ 2;
		while (i > 0)
		{
			if (*temp > *childs[j])
			{
				childs[i] = childs[j];
				i = j;
				j = (i - 1) / 2;
			}
			else
				break;
		}
		childs[j] = temp;
	}
}

void UCTNode::makeMove(char board[10][9])
{
	int src_x = move.src.x;
	int src_y = move.src.y;
	int dst_x = move.tar.x;
	int dst_y = move.tar.y;

	int src_chess_id = board[src_y][src_x];
	int dst_chess_id = board[dst_y][dst_x];

	if (is_Chess(dst_chess_id))
		chess[dst_chess_id]->exist = false;
	chess[src_chess_id]->pos = move.tar;

	board[dst_y][dst_x] = board[src_y][src_x];
	board[src_y][src_x] = NoChess;
}

void UCTNode::backup(int res)
{
	this->hit_cnt++;
	this->win_cnt += res;
	UCTNode * cur = this->parent;
	while (cur != nullptr)
	{
		cur->adjust();
		cur->hit_cnt++;
		cur->win_cnt++;
		cur = cur->parent;
	}
}

void UCTNode::expand(int side, char board[10][9])//
{
	vector<MOVEMENT> moveList;
	if (side == RED)
	{
		for (int i = RedBegin; i <= RedEnd; i++)
			if (chess[i]->exist)
				chess[i]->generateMovement(moveList, board);
	}
	else
	{
		for (int i = BlackBegin; i <= BlackEnd; i++)
			if (chess[i]->exist)
				chess[i]->generateMovement(moveList, board);
	}
	unsigned size = moveList.size();
	childs.resize(size);
	for (unsigned i = 0; i < size; i++)
		childs[i] = new UCTNode(moveList[i], this);
}

UCTNode * UCTree::moveToBestNode(char board[10][9], int & whosTurn)
{
	int move_side = side;
	UCTNode * cur = root;
	while (1)
	{
		unsigned child_size = cur->childs.size();
		if (child_size == 0)//该结点已搜索过但未拓展出子结点
		{
			cur->expand(move_side, board);
			cur = cur->childs[0];//第一个子结点即为未搜索过的结点
			node_cnt++;
			break;//结束循环
		}
		else if (cur->tail == child_size - 1)//cur所有子结点全部搜索过，需要选举
		{
			cur->makeMove(board);//搜索路径经过该结点
			cur = cur->childs[0];//优先队列保证该子节点可信度最高
			
			//继续向下一层搜索,换边
			move_side = (move_side == RED) ? BLACK : RED;
		}
		else//找到最佳结点（cur存在未搜索过的子结点，不需要选举）
		{
			cur->tail++;
			node_cnt++;
			cur = cur->childs[cur->tail];
			break;//结束循环
		}
	}
	//至此，cur为随机模拟的最佳起始源点
	cur->makeMove(board);
	whosTurn = (move_side == RED) ? BLACK : RED;//返回随机模拟的先手阵营
	return cur;
}

void UCTree::getBestMove(MOVEMENT & mvmt)
{
	mvmt = root->childs[0]->move;
}

void UCTree::init()
{
	root = new UCTNode(MOVEMENT());
}

void UCTree::reset()
{
	resetFrom(root);
}

void UCTree::resetFrom(UCTNode * root)
{
	unsigned child_size;
	child_size = root->childs.size();
	if (child_size != 0)
	{
		for (unsigned i = 0; i < child_size; i++)
			resetFrom(root->childs[i]);
	}
	delete root;
}

void GammaGo_v2::play(Board & board, MOVEMENT & mvmt)
{
	storeStatus();
	UCTSearchEngine.init();
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
			m_board[i][j] = board.board[i][j];

	e.seed((unsigned)std::time(0));

	for (int i = 0; i < time; i++)
	{
		int whosTurn;
		UCTNode * end_node = UCTSearchEngine.moveToBestNode(m_board, whosTurn);
		int res = simulateRun(whosTurn);
		end_node->backup(res);
		restoreStatus();
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 9; j++)
				m_board[i][j] = board.board[i][j];
	}

	UCTSearchEngine.getBestMove(mvmt);
}

int GammaGo_v2::simulateRun(int whosTurn)
{
	if (whosTurn == RED)//黑方先手
	{
		int winner;
		MOVEMENT mvmt;
		while (!gameOver(winner, RED))
		{
			//随机生成一种走法
			vector<MOVEMENT> B_mvmt;
			for (int i = BlackBegin; i <= BlackEnd; i++)
				if (chess[i]->exist)
					chess[i]->generateMovement(B_mvmt, m_board);
			assert(B_mvmt.size() != 0);

			uniform_int_distribution<unsigned> B_mvmt_no(0, B_mvmt.size() - 1);
			mvmt = B_mvmt[B_mvmt_no(e)];
			makeMove(mvmt);
			display();

			if (gameOver(winner, BLACK))
				break;

			//随机生成一种走法
			vector<MOVEMENT> R_mvmt;
			for (int i = RedBegin; i <= RedEnd; i++)
				if (chess[i]->exist)
					chess[i]->generateMovement(R_mvmt, m_board);
			assert(R_mvmt.size() != 0);

			uniform_int_distribution<unsigned> R_mvmt_no(0, R_mvmt.size() - 1);
			mvmt = R_mvmt[R_mvmt_no(e)];
			makeMove(mvmt);
			display();

		}
		if (winner == side)
			return true;
		else
			return false;
	}
	else
	{
		int winner;
		MOVEMENT mvmt;
		while (!gameOver(winner, BLACK))
		{
			//随机生成一种走法
			vector<MOVEMENT> R_mvmt;
			for (int i = RedBegin; i <= RedEnd; i++)
				if (chess[i]->exist)
					chess[i]->generateMovement(R_mvmt, m_board);
			assert(R_mvmt.size() != 0);

			uniform_int_distribution<unsigned> R_mvmt_no(0, R_mvmt.size() - 1);
			mvmt = R_mvmt[R_mvmt_no(e)];
			makeMove(mvmt);
			display();

			if (gameOver(winner, RED))
				break;

			//随机生成一种走法
			vector<MOVEMENT> B_mvmt;
			for (int i = BlackBegin; i <= BlackEnd; i++)
				if (chess[i]->exist)
					chess[i]->generateMovement(B_mvmt, m_board);
			assert(B_mvmt.size() != 0);

			uniform_int_distribution<unsigned> B_mvmt_no(0, B_mvmt.size() - 1);
			mvmt = B_mvmt[B_mvmt_no(e)];
			makeMove(mvmt);
			display();
		}

		if (winner == side)
			return true;
		else
			return false;
	}
}

void GammaGo_v2::makeMove(MOVEMENT & mvmt)
{
	int src_x = mvmt.src.x;
	int src_y = mvmt.src.y;
	int dst_x = mvmt.tar.x;
	int dst_y = mvmt.tar.y;

	int src_chess_id = m_board[src_y][src_x];
	int dst_chess_id = m_board[dst_y][dst_x];

	if (is_Chess(dst_chess_id))
		chess[dst_chess_id]->exist = false;
	chess[src_chess_id]->pos = mvmt.tar;

	m_board[dst_y][dst_x] = m_board[src_y][src_x];
	m_board[src_y][src_x] = NoChess;
}

bool GammaGo_v2::gameOver(int & winner, int side)
{
	if (chess[R_KING]->exist && chess[B_KING]->exist)
	{
		if (chess[R_KING]->pos.x == chess[B_KING]->pos.x)//判断两王相遇
		{
			int col = chess[R_KING]->pos.x;
			for (int i = chess[R_KING]->pos.y + 1; i < chess[B_KING]->pos.y; i++)
			{
				if (m_board[i][col] != NoChess)
					return false;
			}
			//两王之间没有任何棋子
			if (side == RED)
				winner = BLACK;
			else
				winner = RED;
			return true;
		}
		else
			return false;
	}
	else
	{
		if (chess[B_KING]->exist && side == BLACK)
			winner = BLACK;
		else if (side == RED)
			winner = RED;
		return true;
	}
}

void GammaGo_v2::storeStatus()
{
	for (int i = 0; i < 32; i++)
	{
		pos_status[i] = chess[i]->pos;
		exist_status[i] = chess[i]->exist;
	}
}

void GammaGo_v2::restoreStatus()
{
	for (int i = 0; i < 32; i++)
	{
		chess[i]->pos = pos_status[i];
		chess[i]->exist = exist_status[i];
	}
}
