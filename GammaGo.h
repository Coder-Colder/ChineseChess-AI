#pragma once
#ifndef GAMMAGO_H
#define GAMMAGO_H

#include"Player.h"
#include<vector>
using namespace std;


class GammaGo:public Player
{
    char s_board[10][9];
    int time;
    int size;
    vector<int> hit_cnt;//命中次数记录
    vector<int> win_cnt;
    vector<MOVEMENT> moveVec;//第一层走子记录
    CHESSPOS pos_status[32];
    bool exist_status[32];
public:
    GammaGo(int time = 500, unsigned char side = RED):time(time), Player(side){}
    virtual ~GammaGo(){}
    virtual void play(Board &board, MOVEMENT &mvmt);
private:
    bool simulateRun();//模拟下棋
    //void getChildMove();//获取下一步
    void makeMove(MOVEMENT &mvmt);//执行走子,返回目标位置棋子编号
    bool gameOver(int & winner, int side);
    void storeStatus();//保存初始棋局
    void restoreStatus();//恢复初始棋局
};

#endif