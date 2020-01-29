#include "Game.h"
#include <iostream>
using namespace std;

Game::Game()
{
    over_flag = GMAEON;
}

int Game::gameStart(int mode)
{
    MOVEMENT mvmt;
    if(mode == MvsM)
    {
        BetaGo machine1;
        BetaGo machine2;
        while(over_flag == GMAEON)
        {
            board.display();
            machine1.play(board,mvmt);
            board.moveNext(mvmt);
            board.display();
            gameOverCheck(BLACK);
            if(over_flag != GMAEON)
                break;
            machine2.play(board,mvmt);
            board.moveNext(mvmt);
            board.display();
            gameOverCheck(RED);
        }
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
    else if(mode == HvsM)
    {
        Human human;
        BetaGo machine;
        while(over_flag == GMAEON)
        {
            board.display();
            human.play(board,mvmt);
            board.moveNext(mvmt);
            board.display();
            gameOverCheck(BLACK);
            if(over_flag != GMAEON)
                break;
            machine.play(board,mvmt);
            board.moveNext(mvmt);
            board.display();
            gameOverCheck(RED);
        }
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

}

void Game::gameOverCheck(int side)
{
    CHESSPOS pos_R;
    CHESSPOS pos_B;
    if(side == RED)
    {
        if(!board.getBKing(pos_B))
            over_flag = RED;
        else
        {
            if(pos_R.x == pos_B.x)
            {
                for(int i = pos_B.y; board.board[i][pos_B.x] != R_KING && i ; i--)
                    if(board.board[i][pos_B.x] != NoChess)
                        return;
                over_flag = BLACK;
            }
        }
    }
    else 
    {
        if(!board.getRKing(pos_R))
            over_flag = BLACK;
        else
        {
            if(pos_R.x == pos_B.x)
            {
                for(int i = pos_R.y; board.board[i][pos_R.x] != B_KING && i ; i++)
                    if(board.board[i][pos_R.x] != NoChess)
                        return;
                over_flag = RED;
            }
        }
    }
}