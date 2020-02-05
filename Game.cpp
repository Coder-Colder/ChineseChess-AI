#include "Game.h"
#include <iostream>
using namespace std;
/*side / oveb_flag*/
#define GMAEON 0

Game::Game(int mode) 
{
    if(mode == MvsM)
    {
        Red = new GammaGo_v2(500, RED);
        Black = new GammaGo_v2(500, BLACK);
    }
    else if(mode == HvsM)
    {
        Red = new GammaGo_v2(20000,RED);
        Black = new Human(BLACK);
    }
    else
    {
        Red = new Human(RED);
        Black = new Human(BLACK);
    }
    over_flag = GMAEON; 
    this->mode = mode;
}

int Game::Start()
{
    MOVEMENT mvmt;
	board.display();
    while(over_flag == GMAEON)
    {
        Red->play(board,mvmt);
        board.moveNext(mvmt);
        board.display();
        gameOverCheck(RED);
        if(over_flag != GMAEON)
            break;
        Black->play(board,mvmt);
        board.moveNext(mvmt);
        board.display();
        gameOverCheck(BLACK);
    }
    
    if(mode == HvsM)
    {
        if(over_flag == BLACK)
        {
            cout<<endl<<endl<<"Congratulations! YOU WIN!!"<<endl<<endl;
            return BLACK;
        }
        else
        {
            cout<<endl<<endl<<"Sorry! YOU LOSE!!"<<endl<<endl;
            return RED;
        }
    }
    else
    {
        if(over_flag == BLACK)
        {
            cout<<endl<<endl<<"BLACK WIN!!"<<endl<<endl;
            return BLACK;
        }
        else
        {
            cout<<endl<<endl<<"RED WIN!!"<<endl<<endl;
            return RED;
        }

    }
}

void Game::gameOverCheck(int side)
{
    CHESSPOS pos_R = chess[R_KING]->pos;
    CHESSPOS pos_B = chess[B_KING]->pos;
    if(side == RED)
    {
        if(chess[B_KING]->exist == false)
            over_flag = RED;
    }
    else 
    {
        if(chess[R_KING]->exist == false)
            over_flag = BLACK;
    }
}