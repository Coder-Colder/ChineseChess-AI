#include"GammaGo.h"
#include<cmath>
#include<ctime>
#include<random>


static default_random_engine e;
static uniform_int_distribution<unsigned> red_no(RedBegin,RedEnd);
static uniform_int_distribution<unsigned> black_no(BlackBegin,BlackEnd);

void GammaGo::play(Board &board, MOVEMENT &mvmt)
{
    moveVec.resize(0);
    hit_cnt.resize(0);
    win_cnt.resize(0);
    storeStatus();
    //生成所有可能的走子
    if(side == RED)
    {
        for(int i = RedBegin; i <= RedEnd; i++)
            if(chess[i]->exist)
                chess[i]->generateMovement(moveVec, board.board);
    }
    else
    {
        for(int i = BlackBegin; i <= BlackEnd; i++)
            if(chess[i]->exist)
                chess[i]->generateMovement(moveVec, board.board);
    }
    size = moveVec.size();
    hit_cnt.assign(size, 0);
    win_cnt.assign(size, 0);

    //拷贝棋盘
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 9; j++)
            s_board[i][j] = board.board[i][j];

    //随机选择走子策略，计算胜率
    uniform_int_distribution<unsigned> u(0, size - 1);
    e.seed(std::time(0));
    for(int i = 0; i < time; i++)
    {
        unsigned move_idx = u(e);
        MOVEMENT m_mvmt = moveVec[move_idx];
        hit_cnt[move_idx]++;
        makeMove(m_mvmt);
        if(simulateRun() == true)//胜利
            win_cnt[move_idx]++;
        restoreStatus();
    }

    //计算最大胜率
    double win_rate = 0.0;
    int idx = 0;
    for(int i = 0; i < size; i++)
    {
        double rate = (hit_cnt[i] == 0) ? 0.0 : win_cnt[i] / hit_cnt[i];
        if(rate > win_rate)
        {
            win_rate = rate;
            idx = i;
        }
    }

    mvmt = moveVec[idx];
}

bool GammaGo::simulateRun()//模拟下棋
{
    if(side == RED)//黑方先手
    {
        int winner;
        MOVEMENT mvmt;
        while(!gameOver(winner))
        {
            //随机找到一个可以移动的棋子
            unsigned B_chess_id = black_no(e);
            while(!chess[B_chess_id]->exist)
                B_chess_id = black_no(e);

            //随机生成一种走法
            vector<MOVEMENT> B_mvmt;
            chess[B_chess_id]->generateMovement(B_mvmt,s_board);
            uniform_int_distribution<unsigned> B_mvmt_no(0, B_mvmt.size() - 1);
            mvmt = B_mvmt[B_mvmt_no(e)];
            makeMove(mvmt);

            if(gameOver(winner))
                break;

            //随机找到一个可以移动的棋子
            unsigned R_chess_id = red_no(e);
            while(!chess[R_chess_id]->exist)
                R_chess_id = black_no(e);

            //随机生成一种走法
            vector<MOVEMENT> R_mvmt;
            chess[R_chess_id]->generateMovement(R_mvmt,s_board);
            uniform_int_distribution<unsigned> R_mvmt_no(0, R_mvmt.size() - 1);
            mvmt = R_mvmt[R_mvmt_no(e)];
            makeMove(mvmt);

        }
        if(winner == RED)
            return true;
        else 
            return false;
    }
    else
    {
        int winner;
        MOVEMENT mvmt;
        while(!gameOver(winner))
        {
            //随机找到一个可以移动的棋子
            unsigned R_chess_id = red_no(e);
            while(!chess[R_chess_id]->exist)
                R_chess_id = black_no(e);

            //随机生成一种走法
            vector<MOVEMENT> R_mvmt;
            chess[R_chess_id]->generateMovement(R_mvmt,s_board);
            uniform_int_distribution<unsigned> R_mvmt_no(0, R_mvmt.size() - 1);
            mvmt = R_mvmt[R_mvmt_no(e)];
            makeMove(mvmt);

            if(gameOver(winner))
                break;

            //随机找到一个可以移动的棋子
            unsigned B_chess_id = black_no(e);
            while(!chess[B_chess_id]->exist)
                B_chess_id = black_no(e);

            //随机生成一种走法
            vector<MOVEMENT> B_mvmt;
            chess[B_chess_id]->generateMovement(B_mvmt,s_board);
            uniform_int_distribution<unsigned> B_mvmt_no(0, B_mvmt.size() - 1);
            mvmt = B_mvmt[B_mvmt_no(e)];
            makeMove(mvmt);
        }

        if(winner == BLACK)
            return true;
        else 
            return false;
    }
    
}
void GammaGo::makeMove(MOVEMENT &mvmt)//执行走子
{
    int src_x = mvmt.src.x;
    int src_y = mvmt.src.y;
    int dst_x = mvmt.tar.x;
    int dst_y = mvmt.tar.y;

    int src_chess_id = s_board[src_y][src_x];
    int dst_chess_id = s_board[dst_y][dst_x];

    if(is_Chess(dst_chess_id))
        chess[dst_chess_id]->exist = false;
    chess[src_chess_id]->setPos(mvmt.tar);
    
    s_board[dst_y][dst_x] = s_board[src_y][src_x];
    s_board[src_y][src_x] = NoChess;
}


void GammaGo::storeStatus()//保存初始棋局
{
    for(int i = 0; i < 32; i++)
    {
        pos_status[i] = chess[i]->pos;
        exist_status[i] = chess[i]->exist;
    }
}
void GammaGo::restoreStatus()//恢复初始棋局
{
    for(int i = 0; i < 32; i++)
    {
        chess[i]->pos = pos_status[i];
        chess[i]->exist = exist_status[i];
    }
}