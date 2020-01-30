#include "Game.h"
#include <iostream>
using namespace std;

R_King      r_king(CHESSPOS(4, 0));
R_Guard     r_guard1(CHESSPOS(3, 0));
R_Guard     r_guard2(CHESSPOS(5, 0));
R_Bishop    r_bishop1(CHESSPOS(2, 0));
R_Bishop    r_bishop2(CHESSPOS(6, 0));
R_Pawn      r_pawn1(CHESSPOS(0, 3));
R_Pawn      r_pawn2(CHESSPOS(2, 3));
R_Pawn      r_pawn3(CHESSPOS(4, 3));
R_Pawn      r_pawn4(CHESSPOS(6, 3));
R_Pawn      r_pawn5(CHESSPOS(8, 3));
R_Horse     r_horse1(CHESSPOS(1, 0));
R_Horse     r_horse2(CHESSPOS(7, 0));
R_Cannon    r_cannon1(CHESSPOS(1, 2));
R_Cannon    r_cannon2(CHESSPOS(7, 2));
R_Car       r_car1(CHESSPOS(0, 0));
R_Car       r_car2(CHESSPOS(8, 0));
B_King      b_king(CHESSPOS(4, 9));
B_Guard     b_guard1(CHESSPOS(3, 9));
B_Guard     b_guard2(CHESSPOS(5, 9));
B_Bishop    b_bishop1(CHESSPOS(2, 9));
B_Bishop    b_bishop2(CHESSPOS(6, 9));
B_Pawn      b_pawn1(CHESSPOS(0, 6));
B_Pawn      b_pawn2(CHESSPOS(2, 6));
B_Pawn      b_pawn3(CHESSPOS(4, 6));
B_Pawn      b_pawn4(CHESSPOS(6, 6));
B_Pawn      b_pawn5(CHESSPOS(8, 6));
B_Horse     b_horse1(CHESSPOS(1, 9));
B_Horse     b_horse2(CHESSPOS(7, 9));
B_Cannon    b_cannon1(CHESSPOS(1, 7));
B_Cannon    b_cannon2(CHESSPOS(7, 7));
B_Car       b_car1(CHESSPOS(0, 9));
B_Car       b_car2(CHESSPOS(8, 9));

Chess * chess[32] ={
    &r_king,
    &r_guard1,
    &r_guard2,
    &r_bishop1,
    &r_bishop2,
    &r_pawn1,
    &r_pawn2,
    &r_pawn3,
    &r_pawn4,
    &r_pawn5,
    &r_horse1,
    &r_horse2,
    &r_cannon1,
    &r_cannon2,
    &r_car1,
    &r_car2,
    &b_king,
    &b_guard1,
    &b_guard2,
    &b_bishop1,
    &b_bishop2,
    &b_pawn1,
    &b_pawn2,
    &b_pawn3,
    &b_pawn4,
    &b_pawn5,
    &b_horse1,
    &b_horse2,
    &b_cannon1,
    &b_cannon2,
    &b_car1,
    &b_car2,
};


/*side / oveb_flag*/
#define GMAEON 0

Game::Game(int mode) 
{
    if(mode == MvsM)
    {
        Red = new GammaGo(100, RED);
        Black = new GammaGo(100, BLACK);
    }
    else if(mode == HvsM)
    {
        Red = new GammaGo(100,RED);
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
    while(over_flag == GMAEON)
    {
        board.display();
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
                for(int i = pos_B.y; board.board[i][pos_B.x] != B_KING && i ; i--)
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