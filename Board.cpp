#include "Board.h"
#include <iostream>
#include <assert.h>
using namespace std;

/*
        0      1      2      3      4      5      6      7      8
    0   車-----馬-----相-----仕-----帥-----仕-----相-----馬-----車
        |      |      |      |  \   |   /  |      |      |      |
        |      |      |      |    \ | /    |      |      |      |
    1   +------+------+------+------+------+------+------+------+-
        |      |      |      |    / | \    |      |      |      |  
        |      |      |      |  /   |   \  |      |      |      |
    2   +------砲-----+------+------+------+------+------砲-----+-
        |      |      |      |      |      |      |      |      |        红
        |      |      |      |      |      |      |      |      |
    3   兵-----+------兵-----+------兵-----+------兵-----+------兵
        |      |      |      |      |      |      |      |      |
        |      |      |      |      |      |      |      |      |
    4   +------+------+------+------+------+------+------+------+-
        |         楚                          汉                |
        |                河                          界         |
    5   +------+------+------+------+------+------+------+------+-
        |      |      |      |      |      |      |      |      |
        |      |      |      |      |      |      |      |      |
    6   卒-----+------卒-----+------卒-----+------卒-----+------卒
        |      |      |      |      |      |      |      |      |
        |      |      |      |      |      |      |      |      |        黑
    7   +------炮-----+------+------+------+------+------炮-----+-
        |      |      |      |  \   |   /  |      |      |      |
        |      |      |      |    \ | /    |      |      |      |
    8   +------+------+------+------+------+------+------+------+-
        |      |      |      |    / | \    |      |      |      |
        |      |      |      |  /   |   \  |      |      |      |
    9   车-----马-----象-----士-----将-----士-----象-----马-----车
*/

Board::Board()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            board[i][j] = NoChess;
        }
    }
    
    /*for(int i = 0 ; i < 32; i++)
    {
        switch (i)
        {
        case R_KING:
            chess[i] = new R_King;
            break;
        case R_GUARD1:
        case R_GUARD2:
            chess[i] = new R_Guard;
            break;
        case R_BISHOP1:
        case R_BISHOP2:
            chess[i] = new R_Bishop;
            break;
        case R_PAWN1:
        case R_PAWN2:
        case R_PAWN3:
        case R_PAWN4:
        case R_PAWN5:
            chess[i] = new R_Pawn;
            break;
        case R_HORSE1:
        case R_HORSE2:
            chess[i] = new R_Horse;
            break;
        case R_CANNON1:
        case R_CANNON2:
            chess[i] = new R_Cannon;
            break;
        case R_CAR1:
        case R_CAR2:
            chess[i] = new R_Car;
            break;

        case B_KING:
            chess[i] = new B_King;
            break;
        case B_GUARD1:
        case B_GUARD2:
            chess[i] = new B_Guard;
            break;
        case B_BISHOP1:
        case B_BISHOP2:
            chess[i] = new B_Bishop;
            break;
        case B_PAWN1:
        case B_PAWN2:
        case B_PAWN3:
        case B_PAWN4:
        case B_PAWN5:
            chess[i] = new B_Pawn;
            break;
        case B_HORSE1:
        case B_HORSE2:
            chess[i] = new B_Horse;
            break;
        case B_CANNON1:
        case B_CANNON2:
            chess[i] = new B_Cannon;
            break;
        case B_CAR1:
        case B_CAR2:
            chess[i] = new B_Car;
            break;
        default:
            assert(0);
        }
    }*/

    board[0][0] = R_CAR1;
    board[0][8] = R_CAR2;
    board[9][0] = B_CAR1;
    board[9][8] = B_CAR2;

    board[0][1] = R_HORSE1;
    board[0][7] = R_HORSE2;
    board[9][1] = B_HORSE1;
    board[9][7] = B_HORSE2;

    board[0][2] = R_BISHOP1;
    board[0][6] = R_BISHOP2;
    board[9][2] = B_BISHOP1;
    board[9][6] = B_BISHOP2;

    board[0][3] = R_GUARD1;
    board[0][5] = R_GUARD2;
    board[9][3] = B_GUARD1;
    board[9][5] = B_GUARD2;

    board[0][4] = R_KING;
    board[9][4] = B_KING;

    board[2][1] = R_CANNON1;
    board[2][7] = R_CANNON2;
    board[7][1] = B_CANNON1;
    board[7][7] = B_CANNON2;

    board[3][0] = R_PAWN1;
    board[3][2] = R_PAWN2;
    board[3][4] = R_PAWN3;
    board[3][6] = R_PAWN4;
    board[3][8] = R_PAWN5;
    board[6][0] = B_PAWN1;
    board[6][2] = B_PAWN2;
    board[6][4] = B_PAWN3;
    board[6][6] = B_PAWN4;
    board[6][8] = B_PAWN5;

}

void Board::display()
{
    cout<<"  ";
    for(int i = 0; i < 9; i++)
        cout<<i<<"      ";
    cout<<endl;
    for(int i = 0; i < 10; i++)
    {
        cout<<i<<" ";
        for(int j = 0; j < 9; j++)
        {
            switch (board[i][j])
            {
            case R_KING:cout<<"帥";
                break;
            case B_KING:cout<<"将";
                break;
            case R_GUARD1:
            case R_GUARD2:cout<<"仕";
                break;
            case B_GUARD1:
            case B_GUARD2:cout<<"士";
                break;
            case R_HORSE1:
            case R_HORSE2:cout<<"馬";
                break;
            case B_HORSE1:
            case B_HORSE2:cout<<"马";
                break;
            case R_BISHOP1:
            case R_BISHOP2:cout<<"相";
                break;
            case B_BISHOP1:
            case B_BISHOP2:cout<<"象";
                break;
            case R_CANNON1:
            case R_CANNON2:cout<<"砲";
                break;
            case B_CANNON1:
            case B_CANNON2:cout<<"炮";
                break;
            case R_CAR1:
            case R_CAR2:cout<<"車";
                break;
            case B_CAR1:
            case B_CAR2:cout<<"车";
                break;
            case R_PAWN1:
            case R_PAWN2:
            case R_PAWN3:
            case R_PAWN4:
            case R_PAWN5:cout<<"兵";
                break;
            case B_PAWN1:
            case B_PAWN2:
            case B_PAWN3:
            case B_PAWN4:
            case B_PAWN5:cout<<"卒";
                break;
            case NoChess:cout<<"+-";
                break;
            }
            if(j != 8)cout<<"-----";
        }
        cout<<endl;
        switch (i)
        {
        case 9:
            break;
        case 0:
        case 7:
            cout<<"  |      |      |      |  \\   |   /  |      |      |      |"<<endl;
            cout<<"  |      |      |      |    \\ | /    |      |      |      |"<<endl;
            break;
        case 1:
        case 8:
            cout<<"  |      |      |      |    / | \\    |      |      |      |"<<endl;
            cout<<"  |      |      |      |  /   |   \\  |      |      |      |"<<endl;
            break;
        case 4:
            cout<<"  |         楚                          汉                |"<<endl;
            cout<<"  |                河                          界         |"<<endl;
            break;
        case 2:
            cout<<"  |      |      |      |      |      |      |      |      |        红"<<endl;
            cout<<"  |      |      |      |      |      |      |      |      |"<<endl;
            break;
        case 6:
            cout<<"  |      |      |      |      |      |      |      |      |"<<endl;
            cout<<"  |      |      |      |      |      |      |      |      |        黑"<<endl;
            break;
        default:
            cout<<"  |      |      |      |      |      |      |      |      |"<<endl;
            cout<<"  |      |      |      |      |      |      |      |      |"<<endl;
            break;
        }
    }
}

void Board::moveNext(MOVEMENT & move)
{
    int src_x = move.src.x;
    int src_y = move.src.y;
    int dst_x = move.tar.x;
    int dst_y = move.tar.y;

    board[dst_y][dst_x] = board[src_y][src_x];
    board[dst_y][dst_x] = board[src_y][src_x];
}

bool Board::getRKing(CHESSPOS & pos)
{
    for(int i = 0; i <= 2; i++)
    {
        for(int j = 3; j <= 5; j++)
            if(board[i][j] == R_KING)
            {
                pos.x = j;
                pos.y = i;
                return true;
            }
    }
    return false;
}
bool Board::getBKing(CHESSPOS & pos)
{
    for(int i = 0; i <= 2; i++)
    {
        for(int j = 3; j <= 5; j++)
            if(board[i][j] == B_KING)
            {
                pos.x = j;
                pos.y = i;
                return true;
            }
    }
    return false;
}
