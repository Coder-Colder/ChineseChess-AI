#include"GammaGo.h"

void GammaGo::play(Board &board, MOVEMENT &mvmt)
{
    if(side == RED)
    {
        for(int i = RedBegin; i <= RedEnd; i++)
        {
            chess[i]->generateMovement()
        }
    }
}

void GammaGo::simulateRun()//模拟下棋
{

}
void GammaGo::makeMove(MOVEMENT &mvmt)//执行走子
{

}
void GammaGo::withdrawMove(MOVEMENT &mvmt)//撤回走子
{

}