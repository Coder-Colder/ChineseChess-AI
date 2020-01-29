#pragma once
#ifndef GAMMAGO_H
#define GAMMAGO_H

#include"Player.h"
#include<vector>
#include<math.h>
using namespace std;

#define MaxMovement 60



class GammaGo:public Player
{
    int s_board[10][9];
    int time;
    vector<MOVEMENT> moveVec;//第一层走子记录
    vector<int> hit_cnt;//命中次数记录
    vector<int> win_cnt;
public:
    GammaGo(int time = 500, unsigned char side = RED):time(time), Player(side){}
    virtual ~GammaGo(){}
    virtual void play(Board &board, MOVEMENT &mvmt);
private:
    void simulateRun();//模拟下棋
    //void getChildMove();//获取下一步
    void makeMove(MOVEMENT &mvmt);//执行走子
    void withdrawMove(MOVEMENT &mvmt);//撤回走子
};

#endif