#pragma once
#ifndef GAMMAGO_V2_H
#define GAMMAGO_V2_H

#include "Player.h"
#include <vector>


#define CONFINDENCE 0.8

#define EndNodeLoseProfit -1
#define EndNodeWinProfit 1
#define NoProfit 0


#define MaxTurn 200


struct UCTNode
{
	int win_cnt;//该节点收益,对手结点收益为负
	unsigned hit_cnt;//该节点的命中数
	MOVEMENT move;//走子方式
	unsigned tail;//已搜索过的子节点指针数组元素的尾索引
	vector<UCTNode*> childs;//子节点指针数组（用于维护成最大堆）
	UCTNode * parent;//父指针

	int depth;
	static int max_depth;

public:
	UCTNode(int depth, const MOVEMENT & mvmt, UCTNode * parent = nullptr)
	{
		win_cnt = 0;
		hit_cnt = 0;
		move = mvmt;
		tail = 0;
		this->parent = parent;
		this->depth = depth;
		childs.resize(0);
	}
	bool operator >(const UCTNode & node);//用于建立子节点优先队列时比较结点置信度
	void adjust();//将子节点指针数组按照置信度维护成最大堆
	void backup(int res);//回溯至根结点
	void expand(int side, char board[10][9]);//根据当前结点的棋局拓展子节点指针数组（当childs_vec为空时调用）       
	int makeMove(MOVEMENT &mvmt, char board[10][9]);//模拟落子以获取子节点状态，返回落子点chess_id
	void unmakeMove(MOVEMENT & mvmt, int chess_id, char board[10][9]);//撤回落子
	bool endCheck(char board[10][9]);//判断子节点中的制胜棋局
};

class UCTree
{
	UCTNode * root;
	int side;//起始点阵营
public:
	UCTree(int side) :side(side), root(nullptr) {}
	UCTNode* moveToBestNode(char board[10][9], int & whosTurn);//寻找最优搜索路径，返回叶子结点
	void getBestMove(MOVEMENT &mvmt);
	void init();//搜索源点初始化
	void reset();//清空搜索信息
	void resetFrom(UCTNode * root);
};

class GammaGo_v2 :public Player
{
	UCTree UCTSearchEngine;//UCT搜索引擎
	CHESSPOS pos_status[32];//记录传入棋子的位置
	bool exist_status[32];//记录传入棋子的存在与否
	char m_board[10][9];//模拟棋盘
	int time;

public:
	GammaGo_v2(int time, int side = RED) :time(time), UCTSearchEngine(side), Player(side){}
	virtual ~GammaGo_v2() {}
	virtual void play(Board &board, MOVEMENT &mvmt);
private:
	int simulateRun(int whosTurn);//随机模拟下棋
	void makeMove(MOVEMENT &mvmt);//执行走子,返回目标位置棋子编号
	bool gameOver(int & winner);
	void storeStatus();//保存初始棋局
	void restoreStatus();//恢复初始棋局
};

#endif
