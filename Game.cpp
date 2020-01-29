#include "Game.h"
#include <iostream>
using namespace std;

R_King      r_king;
R_Guard     r_guard;
R_Bishop    r_bishop;
R_Pawn      r_pawn;
R_Horse     r_horse;
R_Cannon    r_cannon;
R_Car       r_car;
B_King      b_king;
B_Guard     b_guard;
B_Bishop    b_bishop;
B_Pawn      b_pawn;
B_Horse     b_horse;
B_Cannon    b_cannon;
B_Car       b_car;

Chess * chess[32] ={
    &r_king,
    &r_guard,
    &r_guard,
    &r_bishop,
    &r_bishop,
    &r_pawn,
    &r_pawn,
    &r_pawn,
    &r_pawn,
    &r_pawn,
    &r_horse,
    &r_horse,
    &r_cannon,
    &r_cannon,
    &r_car,
    &r_car,
    &b_king,
    &b_guard,
    &b_guard,
    &b_bishop,
    &b_bishop,
    &b_pawn,
    &b_pawn,
    &b_pawn,
    &b_pawn,
    &b_pawn,
    &b_horse,
    &b_horse,
    &b_cannon,
    &b_cannon,
    &b_car,
    &b_car,
};

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