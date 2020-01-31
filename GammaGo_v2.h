#pragma once
#ifndef GAMMAGO_V2_H
#define GAMMAGO_V2_H

#include "Player.h"
#include <vector>


#define CONFINDENCE 1.96

struct UCTNode
{
	unsigned win_cnt;//����
	unsigned hit_cnt;//������
	MOVEMENT move;//���ӷ�ʽ
	unsigned tail;//�����������ӽڵ�ָ������Ԫ�ص�β����
	vector<UCTNode*> childs;//�ӽڵ�ָ�����飨����ά�������ѣ�
	UCTNode * parent;//��ָ��

	//static unsigned node_cnt;//�����������������.cpp��local������

public:
	UCTNode(const MOVEMENT & mvmt, UCTNode * parent = nullptr)
	{
		win_cnt = 0;
		hit_cnt = 0;
		//node_cnt++;
		move = mvmt;
		tail = 0;
		this->parent = parent;
		childs.resize(0);
	}
	bool operator >(const UCTNode & node);//���ڽ����ӽڵ����ȶ���ʱ�ȽϽ�����Ŷ�
	void adjust();//���ӽڵ�ָ�����鰴�����Ŷ�ά��������
	void makeMove(char board[10][9]);//����move��Աִ�иý���Ӧ������
	void backup(int res);//�����������
	void expand(int side, char board[10][9]);//���ݵ�ǰ���������չ�ӽڵ�ָ�����飨��childs_vecΪ��ʱ���ã�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
};

class UCTree
{
	UCTNode * root;
	int side;//��ʼ����Ӫ
public:
	UCTree(int side) :side(side), root(nullptr) {}
	UCTNode* moveToBestNode(char board[10][9], int & whosTurn);//Ѱ����������·��������Ҷ�ӽ��
	void getBestMove(MOVEMENT &mvmt);
	void init();//����Դ���ʼ��
	void reset();//���������Ϣ
	void resetFrom(UCTNode * root);
};

class GammaGo_v2 :public Player
{
	UCTree UCTSearchEngine;//UCT��������
	CHESSPOS pos_status[32];//��¼�������ӵ�λ��
	bool exist_status[32];//��¼�������ӵĴ������
	char m_board[10][9];//ģ������
	int time;

public:
	GammaGo_v2(int time, int side = RED) :time(time), UCTSearchEngine(side), Player(side){}
	virtual ~GammaGo_v2() {}
	virtual void play(Board &board, MOVEMENT &mvmt);
private:
	int simulateRun(int whosTurn);//���ģ������
	void makeMove(MOVEMENT &mvmt);//ִ������,����Ŀ��λ�����ӱ��
	bool gameOver(int & winner, int side);
	void storeStatus();//�����ʼ���
	void restoreStatus();//�ָ���ʼ���
	void display();
};

#endif
